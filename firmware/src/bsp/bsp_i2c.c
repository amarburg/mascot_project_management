

#include <msp430.h>
#include <stdint.h>

#include "bsp_i2c.h"

#include "led.h"



void bsp_i2c_init( void )
{
	// By data sheets
	// 1. Set UCSWRST (BIS.B #UCSWRST,&UCxCTL1).
	// 2. Initialize all eUSCI_B registers with UCSWRST = 1 (including UCxCTL1).
	// 3. Configure ports.
	// 4. Clear UCSWRST using software (BIC.B #UCSWRST,&UCxCTL1).
	// 5. Enable interrupts (optional).
	UCB0CTLW0 |= UCSWRST; 					// eUSCI_B in reset state
	UCB0CTLW0 |= UCMODE_3; 				// I2C slave mode
	UCB0I2COA0 = UCOAEN__ENABLE | I2C_OTHER_ADDR;							// own address is 12hex
	UCB0I2COA1 = UCOAEN__ENABLE | I2C_LIGHT1_PWM_ADDR; 					// own address is 12hex
	UCB0I2COA2 = UCOAEN__ENABLE | I2C_LIGHT2_PWM_ADDR; 					// own address is 12hex
	UCB0I2COA3 = UCOAEN__ENABLE | I2C_JETSON_WATCHDOG_ADDR; 					// own address is 12hex

	P1SEL0    |= BIT2 | BIT3; 				// configure I2C pins (device specific)
	P1SEL1    &= ~(BIT2 | BIT3); 			// configure I2C pins (device specific)
	UCB0CTLW0 &= ~UCSWRST; 						// eUSCI_B in operational state
	UCB0IE    |= UCTXIE3 | UCRXIE3 | UCTXIE2 | UCRXIE2 | UCTXIE1 | UCRXIE1 | UCTXIE0 | UCRXIE0; 		// enable TX&RX-interrupt
	//GIE; // general interrupt enable

	// inside the eUSCI_B TX interrupt service routine
	//UCBxTXBUF = 0x77; // send 077h

	// inside the eUSCI_B RX interrupt service routine
	//data = UCBxRXBUF; // data is the internal variable
}
