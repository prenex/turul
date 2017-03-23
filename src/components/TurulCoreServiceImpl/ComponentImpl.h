#ifndef TURUL_CORE_SERVICE_IMPL_H
#define TURUL_CORE_SERVICE_IMPL_H

/*#include "../AdderService.h"
#include "../PrinterServices.h"
#include "../MainControllerService.h"*/

#include "../TurulCoreService.h"

namespace TurulCoreServiceImpl {
	class ComponentImpl : public TurulCoreService {
	private:
		/*
		AdderService adder;
		PrinterServices printers;
		*/
	public:
		ComponentImpl() {
			TurulCoreService::registerImpl(this);
		}
		virtual bool test();
	};
} // end namespace TurulCoreServiceImpl

// Creating the implementation ensures service reg.
// this will be included before the main, and run before that!
#ifdef LWC_IMPLEMENTATION_MODULES
static TurulCoreServiceImpl::ComponentImpl turulCoreServiceImpl;
#endif

#endif // MAIN_CONTROLLER_SERVICE_IMPL_H
