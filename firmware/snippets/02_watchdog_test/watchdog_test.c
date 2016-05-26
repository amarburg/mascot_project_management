//***************************************************************************************
//  On the TX1 Companion board, LEDs are on P2.4 and P2.5
//***************************************************************************************

#include <msp430.h>

#include "bsp/bsp_digital_io.h"
#include "bsp/bsp_watchdog_timer.h"
#include "led.h"

int main(void) {

		bsp_watchdog_init( true );

    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
		bsp_dio_init();

		led_off( LED1 );
		led_off( LED2 );

		unsigned int loops = 0;
    for(;;) {
        volatile unsigned int i;            // volatile to prevent optimization

        i = 50000;                          // SW Delay
        do i--;
        while(i != 0);

				led_toggle( LED1 );

				if( ++loops < 4 ) {
					bsp_watchdog_touch();
				}

				if( loops > 2 ) {
					led_on(LED2);
				}
    }

    return 0;
}
