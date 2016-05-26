#include "pwm.h"

#include "bsp/bsp_pwm.h"

#define us_per_bit 8

void pwm_set( uint8_t val )
{
	uint16_t ms = 1100 + val*8;
	uint16_t bits = ms >> 3;

	// Calculations
	bsp_pwm_set_bit( bits );
}
