#ifndef SYSTEM_INTERFACE_FLASH_H
#define SYSTEM_INTERFACE_FLASH_H

#include "system/system.h"

namespace sys {
	class iflash {
	public:
		virtual result_t init() = 0;

		virtual result_t volume_size(size_t& size) = 0;
		virtual result_t sector_size(size_t& size) = 0;

		virtual result_t write(uint32_t address, const uint8_t *p_data, size_t size) = 0;
		virtual result_t read(uint32_t address, uint8_t *p_data, size_t size) = 0;

		virtual result_t erase_all() = 0;
		virtual result_t erase_sector(uint32_t address) = 0;

	protected:
		iflash() {}
	};
}


#endif /* SYSTEM_INTERFACE_FLASH_H */