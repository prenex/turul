#define LWC_INTERFACING_MODULES
#include "AdderService.h"
#include "PrinterServices.h"
#include "MainControllerService.h"

// There can be multiple printer services (see interfacing module)
// Here we have two of them (one writes to stdout and other to file)
#define LWC_IMPLEMENTATION_MODULES
#include "SimpleAdderServiceImpl/ComponentImpl.h"
#include "SimplePrinterServiceImpl/ComponentImpl.h"
#include "FilePrinterServiceImpl/ComponentImpl.h"
#include "MainControllerServiceImpl/ComponentImpl.h"

int main() {
	// Run the entry service
	MainControllerService mainControllerService;
	return mainControllerService.run();
}
