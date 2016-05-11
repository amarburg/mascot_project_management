#include "bsp_digital_io.h"


void bsp_dio_set( uint8_t signal, bool active )
{
	assert( DigitalIoSignals[signal] == DigitalIoSignals[signal].signal );

	if( DigitalIoSignals[signal].active == ActiveLow ) active = !active;

	if( active ) {
		DigitalIoSignals[signal].out |= DigitalIoSignals[signal].pin;
	} else {
		DigitalIoSignals[signal].out &= ^DigitalIoSignals[signal].pin;
	}
}
