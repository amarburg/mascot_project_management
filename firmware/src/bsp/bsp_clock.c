
#include "msp430.h"

#include "bsp_clock.h"

void bsp_clock_init( void )
{
	unsigned char i;

	// Set XT1 osc to high freq mode, 6-16MHZ
	CSCTL6 |= XTS_1 | XT1HFFREQ_2;

	// Set Xin and Xout pins to clock mode
	P2SEL1 |=   BIT7 | BIT6;
	P2SEL0 &= ~(BIT7 | BIT6);

	// MCLK = XT1 / 8 = 2MHz.
  // SMCLK = MCLK / 2 = 1MHz
	CSCTL5 |= DIVM__8 | DIVS__2;

	do {
   CSCTL7  &= ~(XT1OFFG + DCOFFG); // Clear XT2,XT1,DCO fault flags
   SFRIFG1 &= ~OFIFG;               // Clear fault flags
   for(i=0;i<0xFF;i++);             // Delay for Osc to stabilize
  } while (SFRIFG1 & OFIFG);     // Test oscillator fault flag

 for(i=0;i<0xFF;i++);       // Delay

	// MCLK and SMCLK come from XT1CLK
	CSCTL4 |= SELMS__XT1CLK;

}
