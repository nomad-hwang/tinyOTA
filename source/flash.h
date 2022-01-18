#ifndef _FLASH_SECTION_H_
#define _FLASH_SECTION_H_

#include <stdint.h>

typedef struct _FLASH_SECTION FLASH_SECTION;

struct _FLASH_SECTION {
	uint32_t    n_startAddr;
	uint32_t    n_size;

	uint32_t	n_pageSize;
};

#endif