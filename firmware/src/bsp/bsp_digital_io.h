#ifndef bsp_digital_io_H
#define bsp_digital_io_H

#include <stdint.h>
#include "config.h"


void bsp_dio_set( uint8_t signal, bool active );

#endif // bsp_digital_io_H
