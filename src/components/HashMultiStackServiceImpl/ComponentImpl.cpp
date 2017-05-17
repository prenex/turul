#include "ComponentImpl.h"
#include "HashStacks.h"

namespace HashMultiStackServiceImpl {
	bool ComponentImpl::test() {
		// Implementers always return 1 here
		// when testing an aggregate
		return true;
	}

	VectorStack bogus;

	Stack& ComponentImpl::operator[] (std::size_t i) {
		return hashStacks[i];
	}
}
