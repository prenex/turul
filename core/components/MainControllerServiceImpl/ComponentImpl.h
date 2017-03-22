#ifndef MAIN_CONTROLLER_SERVICE_IMPL_H
#define MAIN_CONTROLLER_SERVICE_IMPL_H

#include "../AdderService.h"
#include "../PrinterServices.h"
#include "../MainControllerService.h"

namespace MainControllerServiceImpl {
	class ComponentImpl : public MainControllerService {
	private:
		AdderService adder;
		PrinterServices printers;
	public:
		ComponentImpl() {
			MainControllerService::registerMainControllerService(this);
		}
		virtual int run();
	};
}
// Creating the implementation ensures service reg.
// this will be included before the main, and run before that!
#ifdef LWC_IMPLEMENTATION_MODULES
static MainControllerServiceImpl::ComponentImpl mainControllerServiceImpl;
#endif

#endif
