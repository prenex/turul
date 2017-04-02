// The turul stand-alone entry point:
//
// Describe this deployment by defining interfacing modules
// and implementation components for the built binary.
// Also this is where we set configurations parameters
// for the components (if available)

#define LWC_INTERFACING_MODULES
#include "ControllerService.h"
#include "LoggerServices.h"
#include "DictionaryServices.h"
#include "TurulCoreService.h"
#include "IoService.h"

#define LWC_IMPLEMENTATION_MODULES
#include "StandaloneControllerServiceImpl/ComponentImpl.h"
#include "StdLoggerServiceImpl/ComponentImpl.h"
#include "BootDictionaryServiceImpl/ComponentImpl.h"
#include "TurulCoreServiceImpl/ComponentImpl.h"
#include "TBufIoServiceImpl/ComponentImpl.h"

// Service configurations  //

// Set log level for LoggerServices
const LoggerServices::Level LoggerServices::conf_logLevel = LoggerServices::Level::INFO;

// Entry point //
int main(int argc, char* argv[]) {
	// Run the entry point
	ControllerService controllerService;
	return controllerService.run(argc, argv);
}
