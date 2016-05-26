//***************************************************************************************
//  On the TX1 Companion board, LEDs are on P2.4 and P2.5
//***************************************************************************************

#include <msp430.h>

#include "bsp/bsp_digital_io.h"
#include "led.h"

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode
                                            // to activate previously configured port settings
		bsp_dio_init();

		//led_off( LED2 );
		led_on( LED1 );

    for(;;) {
        volatile unsigned int i;            // volatile to prevent optimization

        led_toggle( LED1 );
				//led_toggle( LED2 );

        i = 50000;                          // SW Delay
        do i--;
        while(i != 0);
    }

    return 0;
}
