#ifndef MAIN_CONTROLLER_SERVICE_H
#define MAIN_CONTROLLER_SERVICE_H

// Interfacing module's class
class MainControllerService {
private:
	static MainControllerService* mainControllerServiceImpl;
public:
	// Return the value that should be returned by main
	virtual int run() {
		if(mainControllerServiceImpl != nullptr) {
			return mainControllerServiceImpl->run();
		} else {
			// Big error!
			return 1;
		}
	}
	
	static void registerMainControllerService(MainControllerService* impl) {
		mainControllerServiceImpl = impl;
	}
};
// The variable should be defined in some cpp file
// it will be in the cpp that set this!
#ifdef LWC_INTERFACING_MODULES
MainControllerService *MainControllerService::mainControllerServiceImpl;
#endif

#endif
