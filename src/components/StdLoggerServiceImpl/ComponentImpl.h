#ifndef SIMPLE_PRINTER_SERVICE_IMPL_H
#define SIMPLE_PRINTER_SERVICE_IMPL_H

#include<cstdio>
#include "../LoggerServices.h"

namespace StdLoggerServiceImpl {
	class ComponentImpl : public LoggerServices {
	public:
		ComponentImpl() {
			LoggerServices::registerImpl(this);
		}
		virtual int testServices() {
			// Indicates there is an implementations!
			// Always return 1 in case of implementers 
			// that implement aggregated multiples as
			// the interfacing module sums it up!
			return 1;
		}
	};
}

// Creating the implementation ensures service reg.
// this will be included before the main, and run before that!
#ifdef LWC_IMPLEMENTATION_MODULES
static StdLoggerServiceImpl::ComponentImpl stdLoggerServiceImpl;
#endif

#endif // namespace StdLoggerServiceImpl
