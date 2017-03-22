#ifndef PRINTER_SERVICES_H
#define PRINTER_SERVICES_H

#include<vector>

// Interfacing module's class
// ends with 's' (plural) as there can be multiple implementations!
class PrinterServices {
private:
	static std::vector<PrinterServices*> printerServiceImpls;
public:
	virtual void print(int num) {
		// Do for all of them
		for(PrinterServices* ps : printerServiceImpls) {
			ps->print(num);
		}
	}
	
	static void registerPrinterService(PrinterServices* impl) {
		printerServiceImpls.push_back(impl);
	}
};
// The variable should be defined in some cpp file
// it will be in the cpp that set this!
#ifdef LWC_INTERFACING_MODULES
std::vector<PrinterServices*> PrinterServices::printerServiceImpls;
#endif

#endif
