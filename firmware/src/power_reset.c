
#include <stdbool.h>

#include "power_reset.h"

#include "digital_io.h"
#include "config.h"

#include "bsp/bsp_digital_io.h"

void do_power_jetson( bool press )
{
	bsp_dio_set( POWER_PIN, press );
	//usleep( POWER_ACTIVE_MS * 1000);
	//bsp_dio_set( POWER_PIN, false );
}

void do_reset_jetson( bool press )
{
	bsp_dio_set( RESET_PIN, true );
	//usleep(RESET_ACTIVE_MS * 1000);
	//bsp_dio_set( RESET_PIN, false );
}
