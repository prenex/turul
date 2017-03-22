#ifndef FILE_PRINTER_SERVICE_IMPL_H
#define FILE_PRINTER_SERVICE_IMPL_H

#include<cstdio>

#include "../PrinterServices.h"

namespace FilePrinterServiceImpl {
	class ComponentImpl : public PrinterServices {
	public:
		ComponentImpl() {
			PrinterServices::registerPrinterService(this);
		}
		virtual void print(int num);
	};
}
// Creating the implementation ensures service reg.
// this will be included before the main, and run before that!
#ifdef LWC_IMPLEMENTATION_MODULES
static FilePrinterServiceImpl::ComponentImpl filePrinterServiceImpl;
#endif

#endif
