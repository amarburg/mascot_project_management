#pragma once

#include "config.h"
#include "digital_io.h"

#define LED1 LED1_PIN
#define LED2 LED2_PIN

void led_set( uint8_t which, bool on );
void led_on( uint8_t which );
void led_off( uint8_t which );

void led_toggle( uint8_t which );
