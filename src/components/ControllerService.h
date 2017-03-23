#ifndef CONTROLLER_SERVICE_H
#define CONTROLLER_SERVICE_H

// Interfacing module's class
class ControllerService {
private:
	static ControllerService* serviceImpl;
public:
	// Return the value that should be returned by main
	virtual int run(int argc, char* argv[]) {
		if(serviceImpl != nullptr) {
			return serviceImpl->run(argc, argv);
		} else {
			// Big error: No controller service in the deployment!
			return 1;
		}
	}
	
	static void registerImpl(ControllerService* impl) {
		serviceImpl = impl;
	}
};

// The variable should be defined in some cpp file
// it will be in the cpp that set this!
#ifdef LWC_INTERFACING_MODULES
ControllerService *ControllerService::serviceImpl;
#endif

#endif // CONTROLLER_SERVICE_H
