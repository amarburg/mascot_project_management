#include <msp430fr2311.h>

// Chip-specific configuration

// The equivalent values in the headear file are externs, not constants...
// which makes them unusable to initialize the const structure.
#define _P2OUT (P2_BASE + OFS_P2OUT)
#define _P2DIR (P2_BASE + OFS_P2DIR)

const struct DigitalIoConfig DigitalIoSignals[NUM_DIO_PINS] = {
	{ POWER_PIN, _P2DIR, _P2OUT, BIT2, ActiveHigh },
	{ RESET_PIN, _P2DIR, _P2OUT, BIT3, ActiveHigh },
	{ LED1_PIN,  _P2DIR, _P2OUT, BIT5, ActiveHigh },
	{ LED2_PIN,  _P2DIR, _P2OUT, BIT4, ActiveHigh }
};
