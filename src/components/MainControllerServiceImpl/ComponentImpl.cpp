#include "ComponentImpl.h"

namespace MainControllerServiceImpl {
	int ComponentImpl::run() {
		// TODO: implement main entry logic here
		int result = adder.add(5, 10);
		printers.print(result);

		// This will be the retval of main too
		return 0;
	}
}
