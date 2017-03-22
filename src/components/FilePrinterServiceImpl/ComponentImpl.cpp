#include "ComponentImpl.h"
namespace FilePrinterServiceImpl {
	void ComponentImpl::print(int num) {
		FILE *pFile;
		pFile = fopen ("out.txt","w");
		if (pFile!=NULL) {
			fprintf(pFile, "Number: %d\n", num);
			fclose (pFile);
		}
	}
}
