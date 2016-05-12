
#include "msp430.h"

#include "bsp_clock.h"

void bsp_clock_init( void )
{
	// Set XT1 osc to high freq mode, 6-16MHZ
	CSCTL6 |= XTS_1 | XT1HFFREQ_2;

	// Set Xin and Xout pins to clock mode
	P2SEL1 |=  BIT7 | BIT6;
	P2SEL0 &= ~(BIT7 | BIT6);

	// MCLK = XT1 / 8.  SMCLK = MCLK / 2
	CSCTL5 |= DIVM__8 | DIVS__2;

	// MCLK and SMCLK come from XT1CLK
	CSCTL4 |= SELMS__XT1CLK;

}
