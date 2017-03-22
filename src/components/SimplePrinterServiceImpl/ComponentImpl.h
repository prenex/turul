#ifndef SIMPLE_PRINTER_SERVICE_IMPL_H
#define SIMPLE_PRINTER_SERVICE_IMPL_H

#include<cstdio>

#include "../PrinterServices.h"
namespace SimplePrinterServiceImpl {
	class ComponentImpl : public PrinterServices {
	public:
		ComponentImpl() {
			PrinterServices::registerPrinterService(this);
		}
		virtual void print(int num) {
			printf("Number: %d\n", num);
		}
	};
}
// Creating the implementation ensures service reg.
// this will be included before the main, and run before that!
#ifdef LWC_IMPLEMENTATION_MODULES
static SimplePrinterServiceImpl::ComponentImpl simplePrinterServiceImpl;
#endif

#endif
