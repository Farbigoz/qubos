#ifndef SYSTEM_CLOCK_H
#define SYSTEM_CLOCK_H

#include "system/types.h"


namespace sys {

	class clock {
	public:
		virtual uint32_t get_clock_freq() = 0;
		virtual sys::result_t enable_clock() = 0;
		virtual sys::result_t disable_clock() = 0;
	};

}


#endif /* SYSTEM_CLOCK_H */