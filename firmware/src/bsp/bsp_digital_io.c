
#include "bsp_digital_io.h"

#include "digital_io.h"

void bsp_dio_init()
{
	for( uint8_t i = 0; i < NUM_DIO_PINS; ++i ) {
		*DigitalIoSignals[i].dir |= DigitalIoSignals[i].pin;

		// de-assert signal
		bsp_dio_set( i, 0 );
	}
}


void bsp_dio_set( uint8_t signal, uint8_t i )
{
	//if( DigitalIoSignals[signal].active == ActiveLow ) active = !active;

	if( i ) {
		*DigitalIoSignals[signal].out |= DigitalIoSignals[signal].pin;
	} else {
		*DigitalIoSignals[signal].out &= ~DigitalIoSignals[signal].pin;
	}
}

bool bsp_dio_get( uint8_t signal )
{
	bool state = (*DigitalIoSignals[signal].out |= DigitalIoSignals[signal].pin) != 0;
	//if( DigitalIoSignals[signal].active == ActiveLow ) state = !state;

	return state;
}

bool bsp_dio_toggle( uint8_t signal )
{
	*DigitalIoSignals[signal].out ^= DigitalIoSignals[signal].pin;
}
