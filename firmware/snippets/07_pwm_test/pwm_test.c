//***************************************************************************************
//  On the TX1 Companion board, LEDs are on P2.4 and P2.5
//***************************************************************************************

#include <msp430.h>

#include "bsp/bsp_digital_io.h"
#include "bsp/bsp_watchdog_timer.h"
#include "bsp/bsp_clock.h"
#include "bsp/bsp_timer.h"
#include "pwm.h"
#include "led.h"

// Called every 30ms
void __attribute__((interrupt(TIMER1_B1_VECTOR))) isr_T1B1(void)
{
	if( TB1IV & TBIV__TBIFG ) {
		led_toggle( LED1 );
		bsp_watchdog_touch();

		// Clear LPM0 bits on exit (Wake up!)
		__bic_SR_register_on_exit(LPM0_bits);
	}
}


int main(void) {
		bsp_watchdog_init(false);
		bsp_clock_init();

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
		bsp_dio_init();
		led_off( LED2 );
		led_off( LED1 );

		bsp_timer_init();

		bsp_watchdog_init(true);

		// Enable Interrupts
		//__eint();

		enum { RAMP_UP, NORMAL } state = RAMP_UP;

		const uint8_t BrightnessMax = 255;
		uint8_t brightness = 0;
		char direction = 1;

		unsigned int loops = 0;
    while(true) {
			// Sleep (LPM0 = halt CPU, not much else)
			//LPM0;
			__bis_SR_register(LPM0_bits + GIE);

			if( state == RAMP_UP ) {
				pwm_set( LIGHT1, brightness );

				if( brightness >= BrightnessMax ) state = NORMAL;
			} else {
				pwm_set( LIGHT1, brightness );
				pwm_set( LIGHT2, BrightnessMax-brightness );
			}

			if( brightness >= BrightnessMax ) {
				direction = -1;
			} else if( brightness <= 1 ) {
				direction =  1;
			}

			brightness += direction;

			++loops;
			if( loops % 32 == 0 ) led_toggle(LED2);
    }

    return 0;
}
