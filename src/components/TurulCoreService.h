#ifndef TURUL_CORE_SERVICE_H
#define TURUL_CORE_SERVICE_H

// Interfacing module's class
class TurulCoreService {
private:
	static TurulCoreService* serviceImpl;
public:
	virtual bool test() {
		if(serviceImpl != nullptr) {
			return serviceImpl->test();
		}
	}
	
	static void registerImpl(TurulCoreService* impl) {
		serviceImpl = impl;
	}
};

// The variable should be defined in some cpp file
// it will be in the cpp that set this!
#ifdef LWC_INTERFACING_MODULES
TurulCoreService *TurulCoreService::serviceImpl;
#endif

#endif // TURUL_CORE_SERVICE_H
