#include "unity.h"
#include "pwm.h"
#include "mock_bsp_timer.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_pwm_calculation( void )
{
	bsp_pwm_set_Expect( TIMER1, 0 );
	pwm_set( TIMER1, 0 );

	bsp_pwm_set_Expect( TIMER1, 237 );
	pwm_set( TIMER1, 100 );
}
