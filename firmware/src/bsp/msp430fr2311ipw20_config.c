#include <msp430fr2311.h>

#include "digital_io.h"

// Chip-specific configuration

const struct DigitalIoConfig DigitalIoSignals[NUM_DIO_PINS] = {
	{ POWER_PIN, &P2DIR, &P2OUT, BIT2, ActiveHigh },
	{ RESET_PIN, &P2DIR, &P2OUT, BIT3, ActiveHigh },
	{ LED1_PIN,  &P2DIR, &P2OUT, BIT5, ActiveHigh },
	{ LED2_PIN,  &P2DIR, &P2OUT, BIT4, ActiveHigh }
};
