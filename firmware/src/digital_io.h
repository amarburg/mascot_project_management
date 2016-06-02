#ifndef __DIGITAL_IO_H__
#define __DIGITAL_IO_H__

#include <stdint.h>
#include <stdbool.h>

#define ActiveHigh true
#define ActiveLow false

enum PortDirection { INPUT, OUTPUT };
enum Port { PORT1 = 0,
						PORT2 = 1 };

struct DigitalIoConfig {
	uint8_t signal;
	enum PortDirection direction;
 	enum Port port;
 	uint8_t pin;
};

enum DigitalIOPins {
	POWER_PIN = 0,
	RESET_PIN = 1,
	LED1_PIN = 2,
	LED2_PIN = 3,
	XBEE_DIO0 = 4,
	XBEE_DIO1 = 5,
	NUM_DIO_PINS = 6
};

extern const struct DigitalIoConfig DigitalIoSignals[NUM_DIO_PINS];


#endif
