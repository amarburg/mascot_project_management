

#include "msp430.h"

#include "digital_io.h"
#include "bsp/bsp_digital_io.h"
#include "bsp/bsp_watchdog_timer.h"

// Called every 30msß
void __attribute__((interrupt(TIMER1_B1_VECTOR))) isr_T1B1(void)
{

}

int main( void )
{
	bsp_watchdog_init();
	bsp_clock_init();

	bsp_dio_init();
	bsp_pwm_init();

	while( true ) {
		bsp_watchdog_touch();
	}
}
