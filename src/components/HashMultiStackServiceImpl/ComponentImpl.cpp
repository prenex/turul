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

		// Testing the first few turbostack
		LOGI("3=%d\n" ,mss[0].pop());
		LOGI("1=%d\n" ,mss[0].pop());
		LOGI("4=%d\n" ,mss[1].pop());
		LOGI("2=%d\n" ,mss[1].pop());

		// testing the depth capabilities of the turbostacks
		for(int i = 0; i < 42; ++i) {
			mss[0].push(i);
		}

		for(int i = 0; i < 42; ++i) {
			LOGI("popped back in loop (should be %d): %d", (41 - i), mss[0].pop());
		}

		// Testing depth and access of hash slot based vector stacks
		for(int i = 0; i < 42; ++i) {
			mss[100].push(i);
		}

		for(int i = 0; i < 42; ++i) {
			LOGI("popped back in loop (should be %d): %d", (41 - i), mss[100].pop());
		}


		LOGI("... end of testing HashMultiStackServiceImpl!");
		// TODO: return false if something is wrong
		return true;
	}

	Stack& ComponentImpl::operator[] (std::size_t i) {
		return hashStacks[i];
	}
}
