#ifndef LOGGER_SERVICES_H
#define LOGGER_SERVICES_H

#include<vector>

// Interfacing module's class
// ends with 's' (plural) as there can be multiple implementations!
class LoggerServices {
private:
	static std::vector<LoggerServices*> serviceImpls;
public:
	/** Return the number of implementations */
	virtual int testServices() {
		// Count implementations
		int implCount = 0;
		for(LoggerServices* ls : serviceImpls) {
			implCount += ls->testServices();
		}
		// Return the aggregated count
		return implCount;
	}
	
	static void registerImpl(LoggerServices* impl) {
		serviceImpls.push_back(impl);
	}
};
// The variable should be defined in some cpp file
// it will be in the cpp that set this!
#ifdef LWC_INTERFACING_MODULES
std::vector<LoggerServices*> LoggerServices::serviceImpls;
#endif

#endif // LOGGER_SERVICES_H
