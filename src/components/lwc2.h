// We declare this to be a class template and create manual specializations
// in the implementation components to inject services. This whole file is
// not guarded with ifndef guards for a good reason: the file only serves
// as a delegation point towards including implementation headers.
//
// The idea is this: because the implementation headers are guarder so that
// their content survives preprocessor only if the corresponding interfacing
// header is already included before lwc2.h is included in a file. That way
// this header is only here as a mechanism to choose between the needed 
// component implementations to include (instead of including an implementation
// directly by hand). This way other interfacing components can rely only on
// this lwc2.h file and know that possible implementations are all listed here!

// The declaration of lwc2_inject itself  can be here only if we do a specific
// include guard (as otherwise we would have multiple definition issues).
#ifndef LWC2_INJECT_TEMPLATE
#define LWC2_INJECT_TEMPLATE
// Specialization for this are provided by interfacing modules
template<typename T> class lwc2_inject {};
#endif // LWC2_INJECT_TEMPLATE

// LIST OF IMPLEMENTATION MODULE HEADERS HERE //
// ////////////////////////////////////////// //

// TODO: make an example for compositing components by creating aggregator components
//       - that is how multiplicity is supported in the current de-virtualized system!

#include "StandaloneControllerServiceImpl/ComponentImpl.h"	// Controller for standalone runs
#include "StdLoggerServiceImpl/ComponentImpl.h"			// Logger with stdio logging
//#include "BootDictionaryServiceImpl/ComponentImpl.h"		// Dictionary with the basic words
//#include "TurulCoreServiceImpl/ComponentImpl.h"		// Core turul engine
//#include "TBufIoServiceImpl/ComponentImpl.h"			// The turbo-buf IO service implementation
#include "HashMultiStackServiceImpl/ComponentImpl.h"		// Multi-stack service implemented with cache-friendly stacking
