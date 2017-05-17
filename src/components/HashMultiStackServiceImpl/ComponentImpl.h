#ifndef MULTI_STACK_SERVICE_IMPL_H
#define MULTI_STACK_SERVICE_IMPL_H

#include"../MultiStackService.h"
#include<vector>

#include"HashStacks.h"

/** Simple yet good-enough multi-stack implementation as a service */
namespace HashMultiStackServiceImpl {
	class ComponentImpl : public MultiStackService {
		HashStacks hashStacks;
	public:
		ComponentImpl() {
			MultiStackService::registerImpl(this);
		}
		bool test() const override;

		Stack& operator[] (std::size_t i) override;
	};
}
// Creating the implementation ensures service reg.
// this will be included before the main, and run before that!
#ifdef LWC_IMPLEMENTATION_MODULES
static HashMultiStackServiceImpl::ComponentImpl multiStackServiceImpl;
#endif

#endif // MULTI_STACK_SERVICE_IMPL_H
