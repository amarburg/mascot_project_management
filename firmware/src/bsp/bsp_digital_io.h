#ifndef bsp_digital_io_H
#define bsp_digital_io_H

#include <stdint.h>
#include <stdbool.h>

void bsp_dio_init( void );

void bsp_dio_set( uint8_t signal, bool active );

bool bsp_dio_get( uint8_t signal );

#endif // bsp_digital_io_H
