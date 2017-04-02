#ifndef SIMPLE_PRINTER_SERVICE_IMPL_H
#define SIMPLE_PRINTER_SERVICE_IMPL_H

#include<cstdio>
#include "../LoggerServices.h"

/** Log CRITICAL->WARN to stderr and everything else to stdout. Add newlines in the end. */
namespace StdLoggerServiceImpl {
	/** Log CRITICAL->WARN to stderr and everything else to stdout. Add newlines in the end. */
	class ComponentImpl : public LoggerServices {
	public:
		/** Register our component */
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

		/** Log CRITICAL->WARN to stderr and everything else to stdout. Add newlines in the end. */
		virtual void log(const Level level, char* str) {
			switch(level) {
				case LoggerServices::Level::CRITICAL:
					fprintf(stderr, "CRITICAL: %s", str);
					fprintf(stderr, "\n");
					break;
				case LoggerServices::Level::ERROR:
					fprintf(stderr, "ERROR: %s", str);
					fprintf(stderr, "\n");
					break;
				case LoggerServices::Level::WARN:
					fprintf(stderr, "WARN: %s", str);
					fprintf(stderr, "\n");
					break;
				case LoggerServices::Level::INFO:
					fprintf(stdout, "INFO: %s", str);
					fprintf(stdout, "\n");
					break;
				case LoggerServices::Level::DEBUG:
					fprintf(stdout, "DEBUG: %s", str);
					fprintf(stdout, "\n");
					break;
				case LoggerServices::Level::TRACE:
					fprintf(stdout, "TRACE: %s", str);
					fprintf(stdout, "\n");
					break;
			}
		}
	};
}

// Creating the implementation ensures service reg.
// this will be included before the main, and run before that!
#ifdef LWC_IMPLEMENTATION_MODULES
static StdLoggerServiceImpl::ComponentImpl stdLoggerServiceImpl;
#endif

#endif // namespace StdLoggerServiceImpl
