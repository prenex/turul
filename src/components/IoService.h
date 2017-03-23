#ifndef IO_SERVICE_H
#define IO_SERVICE_H

/** Interfacing module's class */
class IoService {
private:
	static IoService* serviceImpl;
public:

	/** Returns true if service impl is up and running */
	virtual bool testService() {
		if(serviceImpl != nullptr) {
			// 
			return serviceImpl->testService();
		} else {
			// Big error: no implementation
			return false;
		}
	}
	
	static void registerImpl(IoService* impl) {
		serviceImpl = impl;
	}
};

// The variable should be defined in some cpp file
// it will be in the cpp that set this!
#ifdef LWC_INTERFACING_MODULES
IoService *IoService::serviceImpl;
#endif

#endif // IO_SERVICE_H
