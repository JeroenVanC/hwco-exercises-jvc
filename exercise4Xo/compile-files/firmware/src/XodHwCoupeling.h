#ifndef XOODHWC_H
#define XOODHWC_H

#include <stdint.h>

#define XOODYAK_BASE_ADDR 0x81100000

#define  STATE_REG_in_0 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 0 * 4))
#define  STATE_REG_in_1 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 1 * 4))
#define  STATE_REG_in_2 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 2 * 4))
#define  STATE_REG_in_3 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 3 * 4))
#define  STATE_REG_in_4 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 4 * 4))
#define  STATE_REG_in_5 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 5 * 4))
#define  STATE_REG_in_6 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 6 * 4))
#define  STATE_REG_in_7 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 7 * 4))
#define  STATE_REG_in_8 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 8 * 4))
#define  STATE_REG_in_9 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 9 * 4))
#define  STATE_REG_in_10 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 10 * 4))
#define  STATE_REG_in_11 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 11 * 4))

#define  ENABLE_CTRL (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 12 * 4))

#define  STATE_REG_out_0 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 13 * 4))
#define  STATE_REG_out_1 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 14 * 4))
#define  STATE_REG_out_2 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 15 * 4))
#define  STATE_REG_out_3 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 16 * 4))
#define  STATE_REG_out_4 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 17 * 4))
#define  STATE_REG_out_5 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 18 * 4))
#define  STATE_REG_out_6 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 19 * 4))
#define  STATE_REG_out_7 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 20 * 4))
#define  STATE_REG_out_8 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 21 * 4))
#define  STATE_REG_out_9 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 22 * 4))
#define  STATE_REG_out_10 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 23 * 4))
#define  STATE_REG_out_11 (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 24 * 4))

#define  STATE_RND_FINISHED (*(volatile unsigned int *)(XOODYAK_BASE_ADDR + 25 * 4))


void roundHWSW_reg(uint32_t *stateAsWords, uint32_t rc);

#endif