//***************************************************************************************
//  On the TX1 Companion board, LEDs are on P2.4 and P2.5
//***************************************************************************************

#include <msp430.h>

#include "bsp/bsp_digital_io.h"
#include "bsp/bsp_watchdog_timer.h"
#include "bsp/bsp_clock.h"
#include "bsp/bsp_timer.h"
#include "bsp/bsp_i2c.h"
#include "led.h"
#include "pwm.h"


// Called every 30ms
void __attribute__((interrupt(TIMER1_B1_VECTOR))) isr_T1B1(void)
{
	if( TB1IV & TBIV__TBIFG ) {
		// led_toggle( LED1 );
		bsp_watchdog_touch();

		// Clear LPM0 bits on exit (Wake up!)
		__bic_SR_register_on_exit(LPM0_bits);
	}
}

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
						pwm_set( LIGHT2, data );
						break;
	case 0x10:  // Vector 16: TXIFG2
						UCB0TXBUF = pwm_get( LIGHT2 );
						break;
	case 0x12:  // Vector 18: RXIFG1
						data = UCB0RXBUF;
						pwm_set( LIGHT1, data );
						break;
	case 0x14:  // Vector 20: TXIFG1
						UCB0TXBUF = pwm_get( LIGHT1 );
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

void main(void)
{
		bsp_watchdog_init(false);
		bsp_clock_init();

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
		bsp_dio_init();
		led_off( LED2 );
		led_off( LED1 );

		bsp_timer_init();
		bsp_i2c_init();

		bsp_watchdog_init(true);

		// Enable Interrupts
		//__eint();

		unsigned int count = 0;
		unsigned int loops = 0;
    while(true) {
			// Sleep (LPM0 = halt CPU, not much else)
			//LPM0;
			__bis_SR_register(LPM0_bits + GIE);

			++loops;
			if( loops % 32 == 0 ) led_toggle(LED2);

    }
}
