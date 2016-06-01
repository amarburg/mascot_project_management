#include "pwm.h"

#include "bsp/bsp_timer.h"

// Val can range from 0-255
// Scale to 1100-1900 us
void pwm_set( uint8_t which, uint8_t val )
{
	uint16_t bits = 0;

	if( val > 0 ) {
		uint16_t us = 1135 + (val + val + val);
		bits = (us >> TIMER_DIVISOR);
	}

	// Calculations
	bsp_pwm_set( which, bits );
}

uint8_t pwm_get( uint8_t which )
{
	uint16_t bits = bsp_pwm_get( which );

	if( bits == 0 ) return 0;
	bits = ((bits << TIMER_DIVISOR)-1000 ) >> 2;
	return bits;
}
