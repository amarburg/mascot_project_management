#include "unity.h"
#include "pwm.h"
#include "mock_bsp_pwm.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_pwm_calculation( void )
{
	bsp_pwm_set_bit_Expect( 0 );
	pwm_set( 0 );

	bsp_pwm_set_bit_Expect( 237 );
	pwm_set( 100 );
}
