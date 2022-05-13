#ifndef XOODHWC_C
#define XOODHWC_C

#include <stdint.h>
#include "XodHwCoupeling.h"

void roundHWSW_reg(uint32_t *stateAsWords, uint32_t rc)
{
    STATE_REG_in_0 = stateAsWords[0];
    STATE_REG_in_1 = stateAsWords[1];
    STATE_REG_in_2 = stateAsWords[2];
    STATE_REG_in_3 = stateAsWords[3];
    STATE_REG_in_4 = stateAsWords[4];
    STATE_REG_in_5 = stateAsWords[5];
    STATE_REG_in_6 = stateAsWords[6];
    STATE_REG_in_7 = stateAsWords[7];
    STATE_REG_in_8 = stateAsWords[8];
    STATE_REG_in_9 = stateAsWords[9];
    STATE_REG_in_10 = stateAsWords[10];
    STATE_REG_in_11 = stateAsWords[11];
    //STATE_REG_in_11 = 0xFFFFFFFF;

    // 12de register 1 zetten | control-register
    ENABLE_CTRL = 0x00000001U;

    // kijken wanneer de 12 rondes klaar zijn
    while (!(STATE_RND_FINISHED == 0x00000001)) {
        // HW blijft bezig tot 12de ronde
    }

    stateAsWords[0] = STATE_REG_out_0;
    stateAsWords[1] = STATE_REG_out_1;
    stateAsWords[2] = STATE_REG_out_2; 
    stateAsWords[3] = STATE_REG_out_3; 
    stateAsWords[4] = STATE_REG_out_4; 
    stateAsWords[5] = STATE_REG_out_5; 
    stateAsWords[6] = STATE_REG_out_6; 
    stateAsWords[7] = STATE_REG_out_7; 
    stateAsWords[8] = STATE_REG_out_8; 
    stateAsWords[9] = STATE_REG_out_9; 
    stateAsWords[10] = STATE_REG_out_10; 
    stateAsWords[11] = STATE_REG_out_11; 

}

#endif