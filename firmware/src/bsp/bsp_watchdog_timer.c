
#include <msp430.h>

#include "bsp_watchdog_timer.h"

void bsp_watchdog_init( void )
{
	// Configures WDT to use SMCLK / 2^19
	// On power up, SMCLK = 1MHz, this gives 0.5s
	//
	WDTCTL = WDTPW | WDTIS_3;
}

void bsp_watchdog_touch( void )
{
	WDTCTL = WDTPW | WDTCNTCL;
}
