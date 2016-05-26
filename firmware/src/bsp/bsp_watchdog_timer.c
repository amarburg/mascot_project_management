
#include <msp430.h>

#include "bsp_watchdog_timer.h"

void bsp_watchdog_init( bool enable )
{
	// Configures WDT to use SMCLK / 2^19
	// On power up, SMCLK = 1MHz, this gives 0.5s
	//
	if( enable ) {
		WDTCTL = WDTPW | WDTIS_3 | WDTCNTCL;
	} else {
		WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
	}
}

void bsp_watchdog_touch( void )
{
	WDTCTL = WDTPW | ((WDTCTL & 0x00FF) | WDTCNTCL);
}
