#ifndef SINE_DRIVER_H
#define SINE_DRIVER_H

#define SINE_BASE_ADDR 0x81100000

#define SINE_REG_in (*(volatile unsigned int *)(SINE_BASE_ADDR + 0 * 4))
#define SINE_REG_out (*(volatile unsigned int *)(SINE_BASE_ADDR + 1 * 4))

uint32_t sinus(int alpha)
{
    SINE_REG_in = alpha;
    return SINE_REG_out;
}
#endif