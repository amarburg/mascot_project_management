
#include <msp430.h>

#include "bsp_watchdog_timer.h"

void bsp_watchdog_init( bool enable )
{
	// Configures WDT to use ACLK @ 32.768 kHz / 2^15 = 1sec
	//
	if( enable ) {
		WDTCTL = WDTPW | WDTSSEL__ACLK | WDTIS_4  | WDTCNTCL;
	} else {
		WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
	}
}

void bsp_watchdog_touch( void )
{
	WDTCTL = WDTPW | ((WDTCTL & 0x00FF) | WDTCNTCL);
}
