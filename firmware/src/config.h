#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <stdint.h>
#include <stdbool.h>

#define POWER_ACTIVE_MS 10
#define RESET_ACTIVE_MS (POWER_ACTIVE_MS)

#define I2C_JETSON_WATCHDOG_ADDR			0x66
#define I2C_LIGHT1_PWM_ADDR						0x12
#define I2C_LIGHT2_PWM_ADDR						0x13
#define I2C_OTHER_ADDR								0x10

#define JETSON_WATCHDOG_FIRST_LIMIT 100
#define JETSON_WATCHDOG_LIMIT     100

#define LOOP_LENGTH_MS  		 32.768

#define  ON_STARTUP_CYCLES		10
#define START_JETSON_CYCLES  	5
#define JETSON_STARTUP_CYCLES  50

#endif
