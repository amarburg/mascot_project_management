
#include <stdint.h>

#include "jetson_watchdog.h"

#include "led.h"

static uint16_t jwCount;

void jetson_watchdog_init( void )
{
	jwCount = 0;
}

void jetson_watchdog_reset( void )
{
	jwCount = 0;
}

uint16_t jetson_watchdog_count( void )
{
	return jwCount;
}

void jetson_watchdog_service( void )
{
	++jwCount;

	if( jwCount > JETSON_WATCHDOG_LIMIT ) led_toggle( LED1 );
}
