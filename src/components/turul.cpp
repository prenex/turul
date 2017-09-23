// The turul stand-alone entry point:
//
// Describe this deployment by defining interfacing modules
// and implementation components for the built binary.
// Also this is where we set configurations parameters
// for the components (if available)

#include "ControllerService.h"
#include "LoggerService.h"
//#include "DictionaryServices.h"
//#include "TurulCoreService.h"
//#include "MultiStackService.h"
//#include "IoService.h"
#include "lwc2.h" // includes the proper implementations of the modules

// Service configurations  //

// Set log level for the LoggerService
const Logger::Service::Level Logger::Service::conf_logLevel = Logger::Service::Level::TRACE;

// Entry point of the application //
int main(int argc, char* argv[]) {
	// Run the controller service and give the command line parameters
	lwc2_inject<Controller::Service> controllerService;
	return controllerService.run(argc, argv);
}
