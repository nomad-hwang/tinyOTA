#ifndef _CONF_H_
#define _CONF_H_

#include <stdbool.h>


#define CRITICAL_SECTION(n)	(n == 1 ? __enable_irq() : __disable_irq())

#define FLASH_SECTION_COUNT     (3)

#define PACKET_SIZE				(50)

#endif