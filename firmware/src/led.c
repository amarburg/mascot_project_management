#include "led.h"

#include "digital_io.h"

#include "bsp/bsp_digital_io.h"

void led_set( uint8_t which, bool on )
{
	bsp_dio_set( which, on );
}

void led_on( uint8_t which )
{
	bsp_dio_set( which, true );
}

void led_off( uint8_t which )
{
	bsp_dio_set( which, false );
}

void led_toggle( uint8_t which )
{
	bsp_dio_toggle( which );
}
