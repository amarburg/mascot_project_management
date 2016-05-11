#include "unity.h"
#include "led.h"
#include "digital_io.h"
#include "mock_bsp_digital_io.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_led_on(void)
{
	bsp_dio_set_Expect( LED1, true );
	led_on( LED1 );

	bsp_dio_set_Expect( LED2, true );
	led_on( LED2 );

	bsp_dio_set_Expect( LED1, false );
	led_off( LED1 );

	bsp_dio_set_Expect( LED2, false );
	led_off( LED2 );
}
