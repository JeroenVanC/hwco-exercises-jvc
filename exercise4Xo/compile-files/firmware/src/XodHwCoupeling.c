#ifndef XOODHWC_C
#define XOODHWC_C

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

}

#endif