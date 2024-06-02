#ifndef SYSTEM_INTERFACE_PLL_H
#define SYSTEM_INTERFACE_PLL_H

#include "system/interface/pll.h"
#include "system/periphery.h"

namespace sys {
	class ipll : public periphery {
	public:
		virtual result_t init() = 0;

	protected:
		ipll() {}
	};
}

#endif /* SYSTEM_INTERFACE_PLL_H */