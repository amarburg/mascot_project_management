#pragma once

#define TIMER1 1
#define TIMER2 2

#define TIMER_CLOCK_US 1
#define TIMER_DIVISOR 3
#define TIMER_TICK_US      (TIMER_CLOCK_US << TIMER_DIVISOR)
#define TIMER_COUNTER 12
#define TIMER_ROLLOVER_US  (TIMER_TICK_US<<TIMER_COUNTER)

void bsp_timer_init( void );

void bsp_timer_start( void );
void bsp_timer_stop( void );

void bsp_pwm_set( uint8_t which, uint16_t );
uint16_t bsp_pwm_get( uint8_t which );
