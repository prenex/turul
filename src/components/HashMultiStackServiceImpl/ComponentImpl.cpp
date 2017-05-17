#include "ComponentImpl.h"
#include "HashStacks.h"
#include "../LoggerServices.h"

namespace HashMultiStackServiceImpl {
	bool ComponentImpl::test() const {
		LOGI("Testing HashMultiStackServiceImpl...");

		// Run tests for the multistack implementation!
		MultiStackService mss; // DI
		mss[0].push(1);
		mss[1].push(2);
		mss[0].push(3);
		mss[1].push(4);

		LOGI("3=%d\n" ,mss[0].pop());
		LOGI("1=%d\n" ,mss[0].pop());
		LOGI("4=%d\n" ,mss[1].pop());
		LOGI("2=%d\n" ,mss[1].pop());

		for(int i = 0; i < 42; ++i) {
			mss[0].push(i);
		}

		for(int i = 0; i < 42; ++i) {
			LOGI("popped back in loop (should be %d): %d", (41 - i), mss[0].pop());
		}


		LOGI("... end of testing HashMultiStackServiceImpl!");
		// TODO: return false if something is wrong
		return true;
	}

	Stack& ComponentImpl::operator[] (std::size_t i) {
		return hashStacks[i];
	}
}
