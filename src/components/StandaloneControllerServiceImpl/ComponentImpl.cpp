// Generic includes
#include<cstdio>

// These lines might look weird, but think about it!
// The implementation header needs the interfacing ones but
// gets it only if you include these, also you need lwc2.h for
// providing you the template specialization so you need
// that too here!
#include "../ControllerService.h" // Will provide exactly our service
#include "../LoggerService.h" // Logging service and its helper macros
#include "../MultiStackService.h" // Will provide the multistack
#include "../lwc2.h"

// Enable this for unit testing the services
#define TEST_CONTROLLED_SERVICES 1

namespace StandaloneControllerServiceImpl {
#ifdef TEST_CONTROLLED_SERVICES
	// A great place for unit testing it seems...
	void testServices() {
		LOGI("Pinging service implementations...");
		// TODO: use the injected stuff from the class body instead of reinject here!
		lwc2_inject<MultiStack::Service> mss;
		mss.test();
		LOGI("...end of pinging service implementations!");
	}
#endif // TEST_CONTROLLED_SERVICES

	int ComponentImpl::run(int argc, char* argv[]) {
#ifdef TEST_CONTROLLED_SERVICES
		testServices();
#endif // TEST_CONTROLLED_SERVICES

		// This will be the retval of main too
		return 0;
	}
}
