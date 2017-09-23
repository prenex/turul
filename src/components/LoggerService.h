#ifndef LOGGER_SERVICE_H
#define LOGGER_SERVICE_H

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
#define  LOGT(...)  if(Logger::Service::Level::TRACE <= Logger::Service::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); lwc2_inject<Logger::Service> ls; ls.log(Logger::Service::Level::TRACE, lb);}
#define  LOGD(...)  if(Logger::Service::Level::DEBUG <= Logger::Service::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); lwc2_inject<Logger::Service> ls; ls.log(Logger::Service::Level::DEBUG, lb);}
#define  LOGI(...)  if(Logger::Service::Level::INFO <= Logger::Service::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); lwc2_inject<Logger::Service> ls; ls.log(Logger::Service::Level::INFO, lb);}
#define  LOGW(...)  if(Logger::Service::Level::WARN <= Logger::Service::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); lwc2_inject<Logger::Service> ls; ls.log(Logger::Service::Level::WARN, lb);}
#define  LOGE(...)  if(Logger::Service::Level::ERROR <= Logger::Service::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); lwc2_inject<Logger::Service> ls; ls.log(Logger::Service::Level::ERROR, lb);}
#define  LOGC(...)  if(Logger::Service::Level::CRITICAL <= Logger::Service::conf_logLevel){char lb[LOG_MAX]; snprintf(lb, LOG_MAX, __VA_ARGS__); lwc2_inject<Logger::Service> ls; ls.log(Logger::Service::Level::CRITICAL, lb);}

// Interfacing module's class
// ends with 's' (plural) as there can be multiple implementations!
namespace Logger {

class Service {
public:
	/** Possible log levels, later ones log out earlier too */
	enum class Level {CRITICAL=0, ERROR, WARN, INFO, DEBUG, TRACE};
	/** Use this component configuration value to set log level */
	static const Level conf_logLevel;
	
	/**
	 * This is the function to override in your logger implementations.
	 *
	 * In most cases you shouldn't call this directly:
	 * Use one of the provided: LOGT, LOGD, LOGI, LOGW, LOGE, LOGC
	 * macro calls where printf style formatting is supported.
	 *
	 * For using those macros, you do not need a Logger
	 * object dependency-injected, just an #include "Logger.h".
	 * Everything else is handled by the macros for you when you are a user.
	 *
	 * The base Logger class alredy handles the log levels
	 * and only call the implementers services when necessary.
	 * Do not handle that in your implementation as it is not
	 * needed in there and is an unnecessary check only then!
	 */
	virtual void log(const Level level, char* str) = 0;
}; // Service class

} // Logger namespace

#endif // LOGGER_SERVICE_H
