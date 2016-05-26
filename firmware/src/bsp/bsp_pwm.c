
#include "msp430.h"

#include "pwm.h"
#include "bsp_pwm.h"



void bsp_pwm_init( void )
{
// • Write 1 to the TBCLR bit (TBCLR = 1) to clear TBxR, clock divider state, and the counter direction.
// • If necessary, write initial counter value to TBxR.
// • Initialize TBxCCRn.
// • Apply desired configuration to TBxIV, TBIDEX, and TBxCCTLn.
// • Apply desired configuration to TBxCTL including to MC bits.

	// Stop and reset timer
	bsp_pwm_stop();
	TB1CTL |= TBCLR;

	// Timer runs from SMCLK (1MHz)
	// divided by 8  (8us per bit)
	// with a 12-bit counter (32.768 ms/rollover = 30Hz)
	TB1CTL = TBSSEL__SMCLK | ID__8 | CNTL__12;

	TB1CCR1 = 0x3FF;
	TB1CCR2 = 0x3FF;

	// Reset/set mode
	TB1CCTL1 = OUTMOD_7;
	TB1CCTL2 = OUTMOD_7;

	// Enable to overflow interrupt
	TB1CTL |= TBIE_1;

	pwm_set( 0 ); // ==

	// Configure TB1.1 and TB1.2 dio pins
	P2SEL0 |=  BIT0 | BIT1;
	P2SEL1 &= ~(BIT0 | BIT1);

	P2DIR |= BIT0 | BIT1;
}

void bsp_pwm_start( void )
{
	TB1CTL |= (MC__CONTINUOUS | TBCLR);
}

void bsp_pwm_set_bit( uint16_t scalar )
{
	TB1CCR1 = scalar;
	TB1CCR2 = scalar;
}

void bsp_pwm_stop( void )
{
	// Set stop mode
	TB1CTL &= ~(MC__CONTINUOUS | MC__UP);
}
