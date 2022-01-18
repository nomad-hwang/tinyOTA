#include "tinyOta.h"

#include <stdbool.h>

typedef _TINY_OTA TINY_OTA;

typedef int (*flash_write_t)(uint32_t _startAddr, uint8_t *_buf, uint16_t _len);
typedef int (*flash_erase_t)(uint32_t _startAddr, uint16_t _pageCnt);

struct _TINY_OTA {
	flash_write_t		f_writeFlash;
	flash_erase_t		f_eraseFlash;

	FLASH_SECTION	t_flashSection;

	uint8_t			n_packetBuffer[PACKET_SIZE];

	bool			b_otaRunning;
};

#pragma pack(1)
struct _TINY_OTA_PACKKET_HEADER {
	uint16_t 	n_packetIndex;
	uint16_t 	n_packetLen;
};

struct _TINY_OTA_PACKKET_FOOTER {
	uint32_t 	n_crc;
};
#pragma pack



typedef enum {
	TINY_OTA_OK = 0,
	TINY_OTA_ERR,

	TINY_OTA_BUSY,
} TINY_OTA_RET;

void tinyOta_init(TINY_OTA *this) {
	memset(this, 0x00, sizeof(TINY_OTA));

	//this->
}

TINY_OTA_RET tinyOta_start(TINY_OTA *this, FLASH_SECTION _flash, uint32_t _otaBinarySize) {
	if(this->b_otaRunning)
		return TINY_OTA_BUSY;

	if(_otaBinarySize > _flash.n_size)
		return TINY_OTA_ERR;

	this->t_flashSection = _flash;

	// Flash Erase
	uint16_t n_pageEraseCount = _otaBinarySize / _flash.n_pageSize;
	n_pageEraseCount += (_otaBinarySize % _flash.n_pageSize ? 1, 0);

	TINY_OTA_RET ret;
	ret = this->f_eraseFlash(_flash.n_startAddr, n_pageEraseCount);
	if(ret)
		return ret;
		
	
}

TINY_OTA_RET tinyOta_verify(TINY_OTA *this, uint8_t *_buf, uint32_t _len) {
	return TINY_OTA_OK;
}

TINY_OTA_RET tinyOta_append(TINY_OTA *this, uint8_t *_buf, uint32_t _len) {
	if(_len > PACKET_SIZE)
		return TINY_OTA_ERR;

	CRITICAL_SECTION(1);
	memcpy(this->n_packetBuffer, _buf, _len);
	CRITICAL_SECTION(0);

	if(tinyOta_verify(this, _buf, _len) == TINY_OTA_OK) {
		uint32_t nAddr = this->t_flashSection.n_size +
		return this->writeFlash(this,  nAddr,_buf, _len);
	}

	

}