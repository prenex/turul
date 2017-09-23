#ifdef CONTROLLER_SERVICE_H // Ensures they want the service
#ifndef STANDALONE_CONTROLLER_SERVICE_IMPL_H // Normal include guard
#define STANDALONE_CONTROLLER_SERVICE_IMPL_H

#include"../MultiStackService.h"
#include"../lwc2.h"

/* Ensured by the ifdef above is that they already #include "../ControllerService.h" */

namespace StandaloneControllerServiceImpl {
	class ComponentImpl : public Controller::Service {
	private:
		// The multi-stack - TODO: ensure we need her here!
		lwc2_inject<MultiStack::Service> mss;
	public:
		virtual int run(int argc, char *argv[]);
	};
}

// Specializing lwc2_inject with the adder service yields a class 
// that just inherits the above implementation and do not do anything else.
// This way if you write auto adder = lwc2_inject<Whatever::Service>; you get a class
// that is basically just a WhateverImpl::ComponentImpl disguised as the
// lwc2_inject template specialization :-)
//
// To enable aggregation of components, we only declare this, when the aggregator is NOT
// set. This way you need to set this in the beginning of your aggregator component and
// unset in the end of that implementation header - right before its similar line.
// This only supports one possible levels of aggregation, but is better than nothing and
// in really bad cases you can name your ifndef differently to do multi-level stuff, just
// I advise against that architecture anyways...
#ifndef CONTROLLER_SERVICE_INJECT
#define CONTROLLER_SERVICE_INJECT
template<> class lwc2_inject<Controller::Service> : public StandaloneControllerServiceImpl::ComponentImpl {};
#endif // -CONTROLLER_SERVICE_INJECT

#endif // -STANDALONE_CONTROLLER_SERVICE_IMPL_H
#endif // +CONTROLLER_SERVICE_H
