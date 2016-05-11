#include "unity.h"

#include "power_reset.h"
#include "digital_io.h"

#include "mock_bsp_digital_io.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_do_power_jetson(void)
{
	bsp_dio_set_Expect( POWER_PIN, true );
	bsp_dio_set_Expect( POWER_PIN, false );

	do_power_jetson();
}

void test_do_reset_jetson(void)
{
	bsp_dio_set_Expect( RESET_PIN, true );
	bsp_dio_set_Expect( RESET_PIN, false );

	do_reset_jetson();
}
