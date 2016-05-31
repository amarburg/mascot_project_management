//***************************************************************************************
//  On the TX1 Companion board, LEDs are on P2.4 and P2.5
//***************************************************************************************

#include <msp430.h>

#include "bsp/bsp_digital_io.h"
#include "bsp/bsp_watchdog_timer.h"
#include "bsp/bsp_clock.h"
#include "bsp/bsp_timer.h"
#include "led.h"


enum GlobalState {
		ON_STARTUP = 0,
		POWER_JETSON = 1,
		IDLE = 2
} state = ON_STARTUP;

const unsigned int ON_STARTUP_DELAY = 10;
const unsigned int POWER_DELAY = 4;



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

void main(void)
{
		bsp_watchdog_init(false);
		bsp_clock_init();

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
		bsp_dio_init();
		led_off( LED2 );
		led_off( LED1 );

		bsp_pwm_init();

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

			if( state == ON_STARTUP ) {
				if( ++count >= ON_STARTUP_DELAY ) {
					state = POWER_JETSON;
					count = 0;

					bsp_dio_set( POWER_PIN, 1 );
				}
			} else if( state == POWER_JETSON ) {
				++count;
				if( count >= POWER_DELAY ) {
					bsp_dio_set( POWER_PIN, 0 );
				} else if( count >= 2*POWER_DELAY ) {
					bsp_dio_set( POWER_PIN, 1 );
				} else if( count  >= 3*POWER_DELAY) {
					bsp_dio_set( POWER_PIN, 0 );

					state = IDLE;
					count = 0;
				}
			} else {
				;// Idle
			}

    }
}
