// This ifdef guard makes the pre-processor avoid the body of this file
// except if this one here is defined (which means someone included the
// interfacing header). This ensures that we can list all the implementation
// headers in the lwc2.h file and just include that everywhere and this
// automagically includes the right implementation headers for you in your file
// whilst you only directly include lwc2.h and the interfacing module *.h
//
// This is what ensures loose coupling in that way that the plugins can be changed
// easily by modifying the lwc2.h "descriptor" file.
// Rem.: Aggregate components can include interfacings on their own and include the
// implementations too for delegating parts of the work...
#ifdef LOGGER_SERVICE_H
#ifndef STD_LOGGER_SERVICE_IMPL_H
#define STD_LOGGER_SERVICE_IMPL_H // normal include guards

#include<cstdio>
#include "../LoggerService.h"

/** Log CRITICAL->WARN to stderr and everything else to stdout. Add newlines in the end. */
namespace StdLoggerServiceImpl {
	/** Log CRITICAL->WARN to stderr and everything else to stdout. Add newlines in the end. */
	class ComponentImpl : public Logger::Service {
	public:
		/** Log CRITICAL->WARN to stderr and everything else to stdout. Add newlines in the end. */
		virtual void log(const Logger::Service::Level level, char* str) {
			if(level <= Logger::Service::conf_logLevel) {
				switch(level) {
					case Logger::Service::Level::CRITICAL:
						fprintf(stderr, "CRITICAL: %s", str);
						fprintf(stderr, "\n");
						break;
					case Logger::Service::Level::ERROR:
						fprintf(stderr, "ERROR: %s", str);
						fprintf(stderr, "\n");
						break;
					case Logger::Service::Level::WARN:
						fprintf(stderr, "WARN: %s", str);
						fprintf(stderr, "\n");
						break;
					case Logger::Service::Level::INFO:
						fprintf(stdout, "INFO: %s", str);
						fprintf(stdout, "\n");
						break;
					case Logger::Service::Level::DEBUG:
						fprintf(stdout, "DEBUG: %s", str);
						fprintf(stdout, "\n");
						break;
					case Logger::Service::Level::TRACE:
						fprintf(stdout, "TRACE: %s", str);
						fprintf(stdout, "\n");
						break;
				}
			}
		}
	};
} // namespace StdLoggerServiceImpl

// Specializing lwc2_inject with the adder service yields a class 
// that just inherits the above implementation and do not do anything else.
// This way if you write auto comp = lwc2_inject<Whatever::Service>; you get a class
// that is basically just a WhateverServiceImpl::ComponentImpl disguised as the
// lwc2_inject template specialization :-)
//
// To enable aggregation of components, we only declare this, when the aggregator is NOT
// set. This way you need to set this in the beginning of your aggregator component and
// unset in the end of that implementation header - right before its similar line.
// This only supports one possible levels of aggregation, but is better than nothing and
// in really bad cases you can name your ifndef differently to do multi-level stuff, just
// I advise against that architecture anyways...
#ifndef LOGGER_SERVICE_INJECT
#define LOGGER_SERVICE_INJECT
template<> class lwc2_inject<Logger::Service> : public StdLoggerServiceImpl::ComponentImpl {};
#endif // -LOGGER_SERVICE_INJECT

#endif // -STD_LOGGER_SERVICE_IMPL_H
#endif // +LOGGER_SERVICE_H
