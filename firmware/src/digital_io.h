#ifndef __DIGITAL_IO_H__
#define __DIGITAL_IO_H__

#include <stdint.h>
#include <stdbool.h>

#define ActiveHigh true
#define ActiveLow false

struct DigitalIoConfig {
	uint8_t signal;
 	volatile unsigned char *dir, *out;
 	uint8_t pin, pinsel;
	bool active;
};

enum DigitalIOPins {
	POWER_PIN = 0,
	RESET_PIN = 1,
	LED1_PIN = 2,
	LED2_PIN = 3,
	NUM_DIO_PINS = 4
};

extern const struct DigitalIoConfig DigitalIoSignals[NUM_DIO_PINS];


#endif
