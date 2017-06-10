#ifndef LOGGER_SERVICE_H
#define LOGGER_SERVICE_H

#include<vector>
#include<cstdio>

#ifndef LOG_MAX		// You can override:
#define  LOG_MAX 512	// The maximum line length to avoid buffer overruns
#endif

// This component is special because we provide simple shorthands for printf style logging!
#define  LOGT(...)  if(LoggerService::Level::TRACE <= LoggerService::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); auto ls = LoggerService::impl; ls.log(LoggerService::Level::TRACE, lb);}
#define  LOGD(...)  if(LoggerService::Level::DEBUG <= LoggerService::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); auto ls = LoggerService::impl; ls.log(LoggerService::Level::DEBUG, lb);}
#define  LOGI(...)  if(LoggerService::Level::INFO <= LoggerService::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); auto ls = LoggerService::impl; ls.log(LoggerService::Level::INFO, lb);}
#define  LOGW(...)  if(LoggerService::Level::WARN <= LoggerService::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); auto ls = LoggerService::impl; ls.log(LoggerService::Level::WARN, lb);}
#define  LOGE(...)  if(LoggerService::Level::ERROR <= LoggerService::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); auto ls = LoggerService::impl; ls.log(LoggerService::Level::ERROR, lb);}
#define  LOGC(...)  if(LoggerService::Level::CRITICAL <= LoggerService::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); auto ls = LoggerService::impl; ls.log(LoggerService::Level::CRITICAL, lb);}

namespace LoggerService {

/** Possible log levels, later ones log out earlier too */
// Rem.: int specifier is there so that we can use switch-case constructs and convert to integer
enum class Level : int {CRITICAL=0, ERROR, WARN, INFO, DEBUG, TRACE};

/** Use this component configuration value to set log level - defaults to INFO */
Level conf_logLevel = Level::INFO;

/** Simplest service interface */
class ServiceInterface {
public:
	virtual inline bool testService() {
		// Should never happen
		fprintf(stderr, "ERROR: Using empty service interface!");
		return true;
	}


	virtual inline void log(const Level level, char* str) {
		// Should never happen
		fprintf(stderr, "ERROR: Using empty service interface!");
	}
};

// Interfacing module's class
// ends with 's' (plural) as there can be multiple implementations!
template<typename Impl>
class Service : public ServiceInterface {
private:
	Impl serviceImpl = Impl{};
public:
	/** Test service */
	virtual inline bool testService() {
		serviceImpl.testService();
	}
	
	/**
	 * This is the function to override in your logger implementations.
	 *
	 * In most cases you shouldn't call this directly:
	 * Use one of the provided: LOGT, LOGD, LOGI, LOGW, LOGE, LOGC
	 * macro calls where printf style formatting is supported.
	 *
	 * For using those macros, you do not need a LoggerService
	 * object dependency-injected, just an #include "LoggerService.h".
	 * Everything else is handled by the macros for you when you are a user.
	 *
	 * The base LoggerService class alredy handles the log levels
	 * and only call the implementers services when necessary.
	 * Do not handle that in your implementation as it is not
	 * needed in there and is an unnecessary check only then!
	 */
	virtual inline void log(const Level level, char* str) {
		// See if log level is appropriate or not
		if(level <= LoggerService::conf_logLevel) {
			// just call the log function implementation
			serviceImpl.log(level, str);
		}
	}
};

} // end namespace LoggerService

#endif // LOGGER_SERVICE_H
