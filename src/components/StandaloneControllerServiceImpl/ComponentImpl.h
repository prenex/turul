#ifndef STANDALONE_CONTROLLER_SERVICE_IMPL_H
#define STANDALONE_CONTROLLER_SERVICE_IMPL_H

#include "../ControllerService.h"

namespace StandaloneControllerServiceImpl {
	class ComponentImpl : public ControllerService {
	private:
		/*
		AdderService adder;
		PrinterServices printers;
		*/
	public:
		ComponentImpl() {
			ControllerService::registerImpl(this);
		}
		virtual int run(int argc, char *argv[]);
	};
}

// Creating the implementation ensures service reg.
// this will be included before the main, and run before that!
#ifdef LWC_IMPLEMENTATION_MODULES
static StandaloneControllerServiceImpl::ComponentImpl standaloneControllerServiceImpl;
#endif

#endif // STANDALONE_CONTROLLER_SERVICE_IMPL_H
