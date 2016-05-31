
#include <msp430.h>

#include "bsp/bsp_digital_io.h"
#include "bsp/bsp_watchdog_timer.h"
#include "bsp/bsp_clock.h"
#include "bsp/bsp_timer.h"
#include "bsp/bsp_i2c.h"
#include "led.h"
#include "jetson_watchdog.h"


enum GlobalState {
		ON_STARTUP = 0,
		POWER_JETSON = 1,
		IDLE = 2
} state = ON_STARTUP;

const unsigned int ON_STARTUP_DELAY = 10;
const unsigned int POWER_DELAY = 4;





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

		jetson_watchdog_init();

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
