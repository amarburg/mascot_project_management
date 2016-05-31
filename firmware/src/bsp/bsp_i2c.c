

#include <msp430.h>
#include <stdint.h>

#include "bsp_i2c.h"

#include "led.h"

void __attribute__((interrupt(EUSCI_B0_VECTOR))) isr_USCI_B0(void)
{
	uint8_t data;

	led_toggle( LED1 );

	switch(__even_in_range(UCB0IV,0x1e)) {
	case 0x00: // Vector 0: No interrupts
				break;
	case 0x02:  // Vector 2: ALIFG
			break;
	case 0x04:  // Vector 4: NACKIFG
			break;
	case 0x06:  // Vector 6: STTIFG
			break;
	case 0x08:  // Vector 8: STPIFG
			break;
	case 0x0a:  // Vector 10: RXIFG3
						data = UCB0RXBUF;
						break;
	case 0x0c:  // Vector 12: TXIFG3
						UCB0TXBUF = 0x44;
						break;
	case 0x0e:  // Vector 14: RXIFG2
						data = UCB0RXBUF;
						break;
	case 0x10:  // Vector 16: TXIFG2
						UCB0TXBUF = 0x55;
						break;
	case 0x12:  // Vector 18: RXIFG1
						data = UCB0RXBUF;
						break;
	case 0x14:  // Vector 20: TXIFG1
						UCB0TXBUF = 0x66;
						break;
	case 0x16:  // Vector 22: RXIFG0
						data = UCB0RXBUF;
						break;
	case 0x18:  // Vector 24: TXIFG0
						UCB0TXBUF = 0x77; // send 077h
						break;
	case 0x1a:  // Vector 26: BCNTIFG
					break;
	case 0x1c:  // Vector 28: clock low time-out
					break;
	case 0x1e:  // Vector 30: 9th bit
					break;
	default: break;
	}

}

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
	UCB0I2COA0 = UCOAEN__ENABLE | 0x0012; 					// own address is 12hex
	UCB0I2COA1 = UCOAEN__ENABLE | 0x0013; 					// own address is 12hex
	UCB0I2COA2 = UCOAEN__ENABLE | 0x0014; 					// own address is 12hex
	UCB0I2COA3 = UCOAEN__ENABLE | 0x0015; 					// own address is 12hex

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
