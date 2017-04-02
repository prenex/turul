#ifndef LOGGER_SERVICES_H
#define LOGGER_SERVICES_H

#include<vector>
#include<cstdio>

// This component is special because we provide simple shorthands for printf style logging!
// This would be the fastest and most lightweight (in most cases) for full debugging and full std logging:
/*
#define  LOGT(...)  fprintf(stdout, "TRACE: "); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n")
#define  LOGD(...)  fprintf(stdout, "DEBUG: "); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n")
#define  LOGI(...)  fprintf(stdout, "INFO: "); fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n")
#define  LOGW(...)  fprintf(stdout, "WARN: "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#define  LOGE(...)  fprintf(stdout, "ERROR: "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
#define  LOGC(...)  fprintf(stdout, "CRITICAL: "); fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n")
*/
// This have some indirection and is a generic solution for using proper logger service implementations:
#define  LOG_MAX 512	// Maximum line length to avoid buffer overruns
#define  LOGT(...)  if(LoggerServices::Level::TRACE <= LoggerServices::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); LoggerServices ls; ls.log(LoggerServices::Level::TRACE, lb);}
#define  LOGD(...)  if(LoggerServices::Level::DEBUG <= LoggerServices::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); LoggerServices ls; ls.log(LoggerServices::Level::DEBUG, lb);}
#define  LOGI(...)  if(LoggerServices::Level::INFO <= LoggerServices::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); LoggerServices ls; ls.log(LoggerServices::Level::INFO, lb);}
#define  LOGW(...)  if(LoggerServices::Level::WARN <= LoggerServices::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); LoggerServices ls; ls.log(LoggerServices::Level::WARN, lb);}
#define  LOGE(...)  if(LoggerServices::Level::ERROR <= LoggerServices::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); LoggerServices ls; ls.log(LoggerServices::Level::ERROR, lb);}
#define  LOGC(...)  if(LoggerServices::Level::CRITICAL <= LoggerServices::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); LoggerServices ls; ls.log(LoggerServices::Level::CRITICAL, lb);}

// Interfacing module's class
// ends with 's' (plural) as there can be multiple implementations!
class LoggerServices {
private:
	static std::vector<LoggerServices*> serviceImpls;
public:
	/** Possible log levels, later ones log out earlier too */
	enum class Level {CRITICAL=0, ERROR, WARN, INFO, DEBUG, TRACE};
	/** Use this component configuration value to set log level - defaults to INFO */
	static const Level conf_logLevel;
	/** Test services: Return the number of implementations */
	virtual int testServices() {
		// Count implementations
		int implCount = 0;
		for(LoggerServices* ls : serviceImpls) {
			implCount += ls->testServices();
		}
		// Return the aggregated count
		return implCount;
	}
	
	/** Register a logger service using lwc */
	static void registerImpl(LoggerServices* impl) {
		serviceImpls.push_back(impl);
	}

	/**
	 * This is the function to override in your logger implementations.
	 *
	 * In most cases you shouldn't call this directly:
	 * Use one of the provided: LOGT, LOGD, LOGI, LOGW, LOGE, LOGC
	 * macro calls where printf style formatting is supported.
	 *
	 * For using those macros, you do not need a LoggerServices
	 * object dependency-injected, just an #include "LoggerServices.h".
	 * Everything else is handled by the macros for you when you are a user.
	 *
	 * The base LoggerServices class alredy handles the log levels
	 * and only call the implementers services when necessary.
	 * Do not handle that in your implementation as it is not
	 * needed in there and is an unnecessary check only then!
	 */
	virtual void log(const Level level, char* str) {
		// See if log level is appropriate or not
		if(level <= LoggerServices::conf_logLevel) {
			// Iterate over the logger implementations
			// and just call their log function
			for(LoggerServices* ls : serviceImpls) {
				ls->log(level, str);
			}
		}
	}
};
// The variable should be defined in some cpp file
// it will be in the cpp that set this!
#ifdef LWC_INTERFACING_MODULES
std::vector<LoggerServices*> LoggerServices::serviceImpls;
#endif

#endif // LOGGER_SERVICES_H
