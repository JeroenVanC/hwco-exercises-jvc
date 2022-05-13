#include "Xoodyak.h"
#include "XodHwCoupeling.h"
#include "print.h"

static void cyclist_down(struct cyclist *c, unsigned char *Xi, unsigned int Xi_len, unsigned int cd);
static void cyclist_up(struct cyclist *c, unsigned char *Yi, unsigned int Yi_len, unsigned char cu);



void CreateEmptyXoodooState(xoodyak_state *state){
    
    for (int y = 0; y < XOODYAK_NUMOF_PLANES; y++)
        for (int x = 0; x < XOODYAK_NUMOF_SHEETS; x++)
            for (int z = 0; z < XOODYAK_LANESIZE; z++)
                (*state)[y][x][z] = 0;

}

static void Xoodoo_StateToWords(xoodyak_state *state, uint32_t *stateAsWords){

    for (int y = 0; y < XOODYAK_NUMOF_PLANES; y++)
        for (int x = 0; x < XOODYAK_NUMOF_SHEETS; x++)
            stateAsWords[index(x, y)] = (*state)[y][x][0] | ((*state)[y][x][1] << 8) | ((*state)[y][x][2] << 16) | ((*state)[y][x][3] << 24);

}

static void Xoodoo_WordsToState(uint32_t *stateAsWords, xoodyak_state *state){

    for (int y = 0; y < XOODYAK_NUMOF_PLANES; y++)
        for (int x = 0; x < XOODYAK_NUMOF_SHEETS; x++){
            (*state)[y][x][0] = stateAsWords[index(x, y)];
            (*state)[y][x][1] = stateAsWords[index(x, y)] >> 8;
            (*state)[y][x][2] = stateAsWords[index(x, y)] >> 16;
            (*state)[y][x][3] = stateAsWords[index(x, y)] >> 24;
        }

}

void Xoodoo_VectorToState(const unsigned char *vector, xoodyak_state *state){

    for (int y = 0; y < XOODYAK_NUMOF_PLANES; y++)
        for (int x = 0; x < XOODYAK_NUMOF_SHEETS; x++)
            for (int z = 0; z < XOODYAK_LANESIZE; z++)
                (*state)[y][x][z] = *(vector + z + 4*(x + 4*y));

}

void Xoodoo_StateToVector(xoodyak_state *state, unsigned char *vector){

    for (int y = 0; y < XOODYAK_NUMOF_PLANES; y++)
        for (int x = 0; x < XOODYAK_NUMOF_SHEETS; x++)
            for (int z = 0; z < XOODYAK_LANESIZE; z++)
                *(vector + z + 4*(x + 4*y)) = (*state)[y][x][z];

}

void Xoodoo_xorStates(xoodyak_state *inout, xoodyak_state *in2){

    for (int y = 0; y < XOODYAK_NUMOF_PLANES; y++)
        for (int x = 0; x < XOODYAK_NUMOF_SHEETS; x++)
            for (int z = 0; z < XOODYAK_LANESIZE; z++)
                (*inout)[y][x][z] ^= (*in2)[y][x][z];

}

static const uint32_t    RC[XOODYAK_ROUNDS] = {
    _rc12,
    _rc11,
    _rc10,
    _rc9,
    _rc8,
    _rc7,
    _rc6,
    _rc5,
    _rc4,
    _rc3,
    _rc2,
    _rc1
};



static void cyclist_down(struct cyclist *c, unsigned char *Xi, unsigned int Xi_len, unsigned int cd){

    //create vector for the temporary state
    unsigned char tempState[XOODYAK_STATESIZE];
    // first bytes are |Xi|
    for (int i = 0; i < Xi_len; i++){
        tempState[i] = Xi[i];
    }
    //followed by 0x01
    tempState[Xi_len] = 0x01;
    //fill rest of bytes up to the third last with 0x0
    for (int i = (Xi_len+1); i < (XOODYAK_STATESIZE-1); i++){
        tempState[i] = 0x00;
    }
    //last byte depends if this is first input. the breadcrumb is xor'ed with 0x01 if mode is hashed (which it always is for this project) 
    tempState[XOODYAK_STATESIZE-1] = (c->mode == MODE_HASH) ? (cd & 0x01) : cd;

    //convert the tempState vector to xoodyak_state object
    xoodyak_state tempStateObj;
    Xoodoo_VectorToState(tempState, &tempStateObj);
    //xor the cyclist state with the tempstate
    Xoodoo_xorStates(&(c->state), &tempStateObj);

    c->phase = PHASE_D;

}

static void cyclist_up(struct cyclist *c, unsigned char *Yi, unsigned int Yi_len, unsigned char cu){

    Xoodoo_Permute(&(c->state));

    //return correct bytes for squeeze
    unsigned char intermediate[XOODYAK_STATESIZE];
    Xoodoo_StateToVector(&(c->state), intermediate);

    for (int i = 0; i < Yi_len; i++)
        Yi[i] = intermediate[i];

    c->phase = PHASE_U;
}

static void Xoodoo_Round(uint32_t *stateAsWords, uint32_t rc){

    unsigned int x, y;
    uint32_t    B[XOODYAK_NUMOF_SHEETS*XOODYAK_NUMOF_PLANES];
    uint32_t    P[XOODYAK_NUMOF_SHEETS];
    uint32_t    E[XOODYAK_NUMOF_SHEETS];

    //Theta
    for (x=0; x<XOODYAK_NUMOF_SHEETS; ++x)
        P[x] = stateAsWords[index(x,0)] ^ stateAsWords[index(x,1)] ^ stateAsWords[index(x,2)];
    for (x=0; x<XOODYAK_NUMOF_SHEETS; ++x)
        E[x] = ROTL32(P[(x-1)%4], 5) ^ ROTL32(P[(x-1)%4], 14);
    for (x=0; x<XOODYAK_NUMOF_SHEETS; ++x)
        for (y=0; y<XOODYAK_NUMOF_PLANES; ++y)
            stateAsWords[index(x,y)] ^= E[x];

    // for (x=0; x<XOODYAK_NUMOF_SHEETS; ++x)
    //     print_hex(P[x], 8); // deze printen effe loopje anzetten



    //Rho-west: plane shift 
    for (x=0; x<XOODYAK_NUMOF_SHEETS; ++x) {
        B[index(x,1)] = stateAsWords[index(x-1,1)];
        B[index(x,2)] = ROTL32(stateAsWords[index(x,2)], 11);
    }
    for (x=0; x<XOODYAK_NUMOF_SHEETS; ++x) {
        //copy back into state
        stateAsWords[index(x,1)] = B[index(x,1)];
        stateAsWords[index(x,2)] = B[index(x,2)];
    }
        
    //Iota: round constant 
    stateAsWords[0] ^= rc;

    //Chi: non linear layer 
    for (x=0; x<XOODYAK_NUMOF_SHEETS; ++x)
        for (y=0; y<XOODYAK_NUMOF_PLANES; ++y)
            B[index(x,y)] = stateAsWords[index(x,y)] ^ (~stateAsWords[index(x,y+1)] & stateAsWords[index(x,y+2)]);
    for (x=0; x<XOODYAK_NUMOF_SHEETS; ++x)
        for (y=0; y<XOODYAK_NUMOF_PLANES; ++y)
            stateAsWords[index(x, y)] = B[index(x, y)]; //copy back into state

    //Rho-east: plane shift */
    for (x=0; x<XOODYAK_NUMOF_SHEETS; ++x) {
        B[index(x,1)] = ROTL32(stateAsWords[index(x,1)], 1);
        B[index(x,2)] = ROTL32(stateAsWords[index(x+2,2)], 8);
    }
    for (x=0; x<XOODYAK_NUMOF_SHEETS; ++x) {
        stateAsWords[index(x,1)] = B[index(x,1)];
        stateAsWords[index(x,2)] = B[index(x,2)];
    }

}

void Xoodoo_Permute(xoodyak_state *state){

    //more efficient version of state for permuting by using 32-bit words
    uint32_t stateAsWords[XOODYAK_NUMOF_PLANES*XOODYAK_NUMOF_SHEETS];
    Xoodoo_StateToWords(state, stateAsWords);

    // for (int i = 0; i < XOODYAK_ROUNDS; i++){
    //     Xoodoo_Round(stateAsWords, RC[i]);
    //     //print_str("RND");
    // }

    

    // for (int i = 0; i < 12; i++){
    //     print_str("ST:");
    //     print_hex(stateAsWords[i], 8);
    // }
    
    roundHWSW_reg(stateAsWords);

    Xoodoo_WordsToState(stateAsWords, state);

}


void cyclist_initialise_hash(struct cyclist *c){

    CreateEmptyXoodooState(&(c->state));

    c->phase = PHASE_U;
    c->mode = MODE_HASH;
    c->Rabsorb = RABS_HASH;
    c->Rsqueeze = RSQU_HASH;
}

void cyclist_absorb(struct cyclist *c, unsigned char *m, int mlen){

    unsigned int splitLen; //amount of bytes that have to be taken from the message
    unsigned char* discard; //pointer to output of up operation (that is to be discarded)
    unsigned int cd = 0x03;

    do {
        if (c->phase != PHASE_U){
            cyclist_up(c, discard, 0, 0);
        }  
        splitLen = (unsigned int)minimum(mlen, c->Rabsorb);
        cyclist_down(c, m, splitLen, cd);
        cd = 0;
        m += splitLen; //point to next block to be processed
        mlen -= splitLen;

    } while ( mlen != 0);
}

void cyclist_squeeze(struct cyclist *c, unsigned char *m, int mlen, unsigned char breadcrumb){

    unsigned int len;
    unsigned char* nothing; //for pointing to nothing in down operation

    len = (unsigned int)minimum(mlen, c->Rsqueeze);
    cyclist_up(c, m, len, breadcrumb);
    m += len;
    mlen -= len;
    while (mlen != 0){
        cyclist_down(c, nothing, 0, 0);
        len = (unsigned int)minimum(mlen, c->Rsqueeze);
        cyclist_up(c, m, len, 0);
        m += len;
        mlen -= len;
    }

}