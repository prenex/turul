// Generic includes
#include<cstdio>
// Local includes
#include "ComponentImpl.h"
// Logging service and its macros
#include"../LoggerService.h"
// Component usage includes

// Uncomment if you want to see the service binding tests
#define TEST_SERVICE_BINDINGS 1

namespace StandaloneControllerServiceImpl {
#ifdef TEST_SERVICE_BINDINGS

	void testServices() {
		LOGI("Pinging service implementations...");
		// Test logger service bindings
		auto ls = LoggerService::impl;
		LOGI(" - %d LoggerService implementations work", ls.testService());
		// TODO: Test if other service implementations are available
		LOGI("...end of pinging service implementations!");
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
