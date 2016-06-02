
#include <msp430.h>

#include "bsp_digital_io.h"

#include "digital_io.h"

struct PortMappingStruct {
	volatile unsigned char *dir, *in, *out;
} PortMapping[] = { { &P1DIR, &P1IN, &P1OUT },
										{ &P2DIR, &P2IN, &P2OUT} };


void bsp_dio_init()
{
	for( uint8_t i = 0; i < NUM_DIO_PINS; ++i ) {
		const enum Port p = DigitalIoSignals[i].port;

		if( DigitalIoSignals[i].direction == OUTPUT ) {
			*PortMapping[p].dir |= DigitalIoSignals[i].pin;
			bsp_dio_set( i, 0 );
		} else {
			*PortMapping[p].dir &= ~DigitalIoSignals[i].pin;
		}
	}
}


void bsp_dio_set( uint8_t signal, uint8_t i )
{
	const enum Port p = DigitalIoSignals[signal].port;

	//if( DigitalIoSignals[signal].active == ActiveLow ) active = !active;
	if( i ) {
		*PortMapping[p].out |= DigitalIoSignals[signal].pin;
	} else {
		*PortMapping[p].out &= ~DigitalIoSignals[signal].pin;
	}
}

bool bsp_dio_get( uint8_t signal )
{
	return (*PortMapping[DigitalIoSignals[signal].port].in |= DigitalIoSignals[signal].pin) != 0;
}

void bsp_dio_toggle( uint8_t signal )
{
	const enum Port p = DigitalIoSignals[signal].port;

	*PortMapping[p].out ^= DigitalIoSignals[signal].pin;
}
