#include "unity.h"

#include "config.h"
#include "digital_io.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_digital_io_table( void )
{
	uint8_t configSize = sizeof(DigitalIoSignals)/sizeof(struct DigitalIoConfig);

	TEST_ASSERT( configSize == NUM_DIO_PINS );

	for( unsigned int i = 0; i < configSize; ++i ) {
		TEST_ASSERT( DigitalIoSignals[i].signal == i );
	}
}
