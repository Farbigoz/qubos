#ifndef SYSTEM_INTERFACE_ONEWIRE_H
#define SYSTEM_INTERFACE_ONEWIRE_H

#include "system/types.h"
#include "system/periphery.h"
#include "system/signal.h"


namespace sys {

	class ionewire : public periphery {
	// Constants
	public:
		const static size_t ROM_SIZE = 8;

	// Enums
	public:
		typedef enum COMMAND_T : uint8_t {
			CMD_SKIP_ROM   = 0xCC,
			CMD_SEARCH_ROM = 0xF0,
			CMD_MATCH_ROM  = 0x55,
		} command_t;

	// Structures
	public:
		typedef union {
			struct {
				uint8_t family;
				uint8_t rom[6];
				uint8_t crc;
			};

			uint8_t raw[ROM_SIZE];
		} address_t;

	public:
		virtual result_t init() = 0;

		virtual result_t reset() = 0;

		virtual result_t transmit(const uint8_t *p_data, size_t size) = 0;
		virtual result_t receive(uint8_t *p_data, size_t size) = 0;

		virtual result_t transmit_cmd(uint8_t cmd);
		virtual result_t transmit_cmd(address_t addr, uint8_t cmd);

		virtual result_t research() = 0;
		virtual result_t search(address_t&) = 0;

	protected:
		ionewire() {}
	};

	result_t ionewire::transmit_cmd(uint8_t cmd) {
		uint8_t data[] = {CMD_SKIP_ROM, cmd};
		return transmit(data, sizeof(data));
	}

	result_t ionewire::transmit_cmd(address_t addr, uint8_t cmd) {
		uint8_t data[sizeof(command_t) + sizeof(address_t) + sizeof(command_t)];

		data[0] = CMD_MATCH_ROM;
		for (int i = 0; i < ROM_SIZE; i++) data[1+i] = addr.raw[i];
		data[9] = cmd;

		return transmit(data, sizeof(data));
	}
}


#endif /* SYSTEM_INTERFACE_ONEWIRE_H */