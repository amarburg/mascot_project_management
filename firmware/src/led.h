#ifndef led_H
#define led_H

#include "config.h"

#define LED1 LED1_PIN
#define LED2 LED2_PIN

void led_on( uint8_t which );
void led_off( uint8_t which );


#endif // led_H
