// This ifdef guard makes the pre-processor avoid the body of this file
// except if MULTI_STACK_SERVICE_H is defined (which means someone included the
// interfacing header). This ensures that we can list all the implementation
// headers in the lwc2.h file and just include that everywhere and this
// automagically includes the right implementation headers for you in your file
// whilst you only directly include lwc2.h and the interfacing module *.h
//
// This is what ensures loose coupling in that way that the plugins can be changed
// easily by modifying the lwc2.h "descriptor" file.
// Rem.: Aggregate components can include interfacings on their own and include the
// implementations too for delegating parts of the work...
#ifdef MULTI_STACK_SERVICE_H
#ifndef HASH_MULTI_STACK_SERVICE_IMPL_H
#define HASH_MULTI_STACK_SERVICE_IMPL_H // Normal include guards are needed too

#include<vector>
#include"HashStacks.h"

/* Rem.: The first ifdef abode ensures that they already #include"../MultiStackService.h" */

/** Simple yet good-enough multi-stack implementation as a service */
namespace HashMultiStackServiceImpl {
	class ComponentImpl : public MultiStack::Service {
		HashStacks hashStacks;	// Stacks
		VectorStack stashArea;	// Stash area
	public:
		bool test() const override;

		MultiStack::Stack& operator[] (std::size_t i) override;

		/** Stash away the top elem of the ith stack to the stash-stack */
		void nstash(std::size_t i, std::size_t n) override;

		/** Pushes an elem to the ith stach from the top of the stash-away stack */
		void nunstash(std::size_t i, std::size_t n) override;

		/** Stash away the top elem of the ith stack to the stash-stack */
		void stash(std::size_t i) override;

		/** Pushes an elem to the ith stach from the top of the stash-away stack */
		void unstash(std::size_t i) override;
	};
}
// Specializing lwc2_inject with the adder service yields a class 
// that just inherits the above implementation and do not do anything else.
// This way if you write auto comp = lwc2_inject<Whatever::Service>; you get a class
// that is basically just a WhateverImpl::ComponentImpl disguised as the
// lwc2_inject template specialization :-)
//
// To enable aggregation of components, we only declare this, when the aggregator is NOT
// set. This way you need to set this in the beginning of your aggregator component and
// unset in the end of that implementation header - right before its similar line.
// This only supports one possible levels of aggregation, but is better than nothing and
// in really bad cases you can name your ifndef differently to do multi-level stuff, just
// I advise against that architecture anyways...
#ifndef MULTI_STACK_SERVICE_INJECT
#define MULTI_STACK_SERVICE_INJECT
template<> class lwc2_inject<MultiStack::Service> : public HashMultiStackServiceImpl::ComponentImpl {};
#endif // -MULTI_STACK_SERVICE_INJECT

#endif // -HASH_MULTI_STACK_SERVICE_IMPL_H
#endif // +MULTI_STACK_SERVICE_H
