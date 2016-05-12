

#include "digital_io.h"
#include "bsp/bsp_digital_io.h"
#include "bsp/bsp_watchdog_timer.h"


int main( void )
{
	bsp_watchdog_init();
	bsp_clock_init();

	bsp_dio_init();

	while( true ) {
		bsp_watchdog_touch();
	}
}
