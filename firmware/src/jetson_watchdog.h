#pragma once

#include <stdint.h>

void jetson_watchdog_init( void );

void jetson_watchdog_reset( void );

uint16_t jetson_watchdog_count( void );

void jetson_watchdog_service( void );
