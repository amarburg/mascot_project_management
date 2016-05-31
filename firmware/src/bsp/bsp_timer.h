#pragma once

#define TIMER1 1
#define TIMER2 2

void bsp_timer_init( void );

void bsp_timer_start( void );
void bsp_timer_stop( void );

void bsp_pwm_set( uint8_t which, uint16_t );
uint16_t bsp_pwm_get( uint8_t which );
