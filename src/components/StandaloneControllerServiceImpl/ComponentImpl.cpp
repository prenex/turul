// Generic includes
#include<cstdio>
// Local includes
#include "ComponentImpl.h"
// Component usage includes
#include"../LoggerServices.h"

// Uncomment if you want to see the service binding tests
#define TEST_SERVICE_BINDINGS 1

namespace StandaloneControllerServiceImpl {
#ifdef TEST_SERVICE_BINDINGS

	void testServices() {
		printf("Pinging service implementations...\n");
		// Test logger service bindings
		LoggerServices ls;
		printf(" - %d LoggerService implementations\n", ls.testServices());
		// TODO: Test if other service implementations are available
		printf("...end of pinging service implementations!\n");
	}
#endif

	int ComponentImpl::run(int argc, char* argv[]) {
#ifdef TEST_SERVICE_BINDINGS
		// Test if service implementations are available
		testServices();
#endif

		// This will be the retval of main too
		return 0;
	}
}
