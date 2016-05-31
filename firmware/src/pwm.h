#ifndef pwm_H
#define pwm_H

#include <stdint.h>
#include "bsp/bsp_timer.h"

#define LIGHT1  TIMER1
#define LIGHT2  TIMER2

// Scaled from 0 - 255
void pwm_set( uint8_t which, uint8_t val );

uint8_t pwm_get( uint8_t which );

#endif // pwm_H
