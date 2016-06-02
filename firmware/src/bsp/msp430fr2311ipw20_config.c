#include <msp430fr2311.h>

#include "digital_io.h"

// Chip-specific configuration

const struct DigitalIoConfig DigitalIoSignals[NUM_DIO_PINS] = {
	{ POWER_PIN, OUTPUT, PORT2, BIT2  },
	{ RESET_PIN, OUTPUT, PORT2, BIT3  },
	{ LED1_PIN,  OUTPUT, PORT2, BIT5  },
	{ LED2_PIN,  OUTPUT, PORT2, BIT4 },
	{ XBEE_DIO0, INPUT,  PORT1, BIT1 },
	{ XBEE_DIO1, INPUT,  PORT1, BIT1 }
};
