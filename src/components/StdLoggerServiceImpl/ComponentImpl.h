#ifndef STD_LOGGER_SERVICE_IMPL_H
#define STD_LOGGER_SERVICE_IMPL_H

#include<cstdio>
#include "../LoggerService.h"

/** Log CRITICAL->WARN to stderr and everything else to stdout. Add newlines in the end. */
namespace StdLoggerServiceImpl {
	/** Log CRITICAL->WARN to stderr and everything else to stdout. Add newlines in the end. */
	// Rem.: final is better here to aid de-virtualization even more (also it makes sense)
	// Rem.: void* is really ugly here but unused! We only inherit to inherit the interface and override safely!
	//       Actually providing void* here "ensures" really that we override the interface otherwise we face (sadly obscure) errors!
	class ComponentImpl final : public LoggerService::Service<LoggerService::ServiceInterface> {
	public:
		// Rem.: inline is a hint here, but likely will work
		//       because we are final, it should get inlined easily!
		inline bool testService() override {
			// Indicates there is an implementations!
			// Always return 1 in case of implementers 
			// that implement aggregated multiples as
			// the interfacing module sums it up!
			return true;
		}

		/** Log CRITICAL->WARN to stderr and everything else to stdout. Add newlines in the end. */
		inline void log(const LoggerService::Level level, char* str) override {
			switch(level) {
				case LoggerService::Level::CRITICAL:
					fprintf(stderr, "CRITICAL: %s", str);
					fprintf(stderr, "\n");
					break;
				case LoggerService::Level::ERROR:
					fprintf(stderr, "ERROR: %s", str);
					fprintf(stderr, "\n");
					break;
				case LoggerService::Level::WARN:
					fprintf(stderr, "WARN: %s", str);
					fprintf(stderr, "\n");
					break;
				case LoggerService::Level::INFO:
					fprintf(stdout, "INFO: %s", str);
					fprintf(stdout, "\n");
					break;
				case LoggerService::Level::DEBUG:
					fprintf(stdout, "DEBUG: %s", str);
					fprintf(stdout, "\n");
					break;
				case LoggerService::Level::TRACE:
					fprintf(stdout, "TRACE: %s", str);
					fprintf(stdout, "\n");
					break;
			}
		}
	};
} // namespace StdLoggerServiceImpl


// Creating the implementation ensures service reg.
// this will be included before the main, and run before that!
#ifdef LWC_IMPLEMENTATION_MODULES
// This ifndef is here to let us create composite LOGGER services from many logger services if we want!
// The composite implementation should be the first that is read in the main entry point by the compiler
// so that we can set this value in the composite when necessary. That way giving in this implementation
// in the component descriptor includes at entry point will work - but also including this file from a
// composite implementation will work too. Otherwise that include would bubble up to the main entry and
// we would end up having double definition of the variable below which is an error. Also this helps to
// maintain integrity as it is an error to have multiple implementations
#ifndef HAS_LOGGER_SERVICE
#define HAS_LOGGER_SERVICE
// LoggerService::impl always contains the current implementation then!
namespace LoggerService {
	static LoggerService::Service<StdLoggerServiceImpl::ComponentImpl> impl;
}
#else
// "Error message" when compiled with a bad setup :-)
ERROR - we can have only one (non-composite) service implementation!
#endif // HAS_LOGGER_SERVICE
#endif // LWC_IMPLEMENTATION_MODULES

#endif // STD_LOGGER_SERVICE_IMPL_H
