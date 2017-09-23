#ifndef HASH_STACKS_H
#define HASH_STACKS_H

#include"../LoggerService.h"
#include"../MultiStackService.h"
#include"../lwc2.h"
#include<vector>
#include<unordered_map> // Contains unordered_map

// Use this for overriding the length or depth of the 'turbo' part that is cache-optimized.
// This applies to the first 8 stacks and they will be chached with this depth.
// Rem.: Use with care as bigger values might compromise performance even if you have
//       a lot of cache memory because of the cache 'lines'. With small values, (for ex. 4)
//       the cache lines for small-stack optimization turbo caching of stack 1..4 will
//       all end up in the very same cache line if we consider 32 bit machines. At least
//       the first two stacks will share cache lines on 64 bit machines too. If a user
//       is using this system more as a storage for variables, this helps speed a lot!
//       If the user uses the stack system for deep stacks, this small optimization
//       will not compromise that performance as the deeper levels are represented in
//       an other way in which consequtive elements of the stacks are after each then...
//       This turbo-ing only make an effect if we use a very small depth and 1..8 stacks.
#ifndef STACK_TURBO_DEPTH
#define STACK_TURBO_DEPTH 4 // ADJUSTABLE!
#endif

// REALLY A CONST VALUE (do not change):
// Stack 0..7 are directly accessed whilst stacks 8..F (other half) are the hashed part.
// DO NOT CHANGE this way we can easily parse from hex values of [0..F] digit by digit (fast)!
#define STACK_BREADTH 8 // NOT ADJUSTABLE!

namespace HashMultiStackServiceImpl {

	/** Stack implemented with a vector */
	class VectorStack final : public MultiStack::Stack {
		std::vector<STACK_DATA_TYPE> v;
	public:
		/** The size of this stack is the size of the underlying vector */
		std::size_t size() const override {
			return v.size();
		}

		/** Gets the ith element of the stack - where index 0 is the top and 1 is the second elem. */
		const STACK_DATA_TYPE& operator[](std::size_t i) const override {
			// Simple indexing trick only
			return v[v.size() - 1 - i];
		}

		/** Gets the top element of the stack */
		const STACK_DATA_TYPE& top() const override {
			return v[v.size() - 1];
		}

		/** Push copy of the given elem on top of the stack */
		void push(STACK_DATA_TYPE elem) override {
			LOGT("PUSH-VECTOR");
			v.push_back(elem);
		}

		/** Get the top element of the stack and shrink the stack */
		STACK_DATA_TYPE pop() {
			LOGT("POP-VECTOR");
			STACK_DATA_TYPE dt = this->top();
			v.pop_back();
			return dt;
		}
	};

	/**
	 * A stack implemented by a turbo-area and a vector-stack (if the element length is too much).
	 * Uses the STACK_TURBO_DEPTH and STACK_DATA_TYPE macros and expect properly sized turbo area.
	 * See: HashStacks class below
	 */
	class TurboStack final : public MultiStack::Stack {
		std::size_t stackSize = 0;
		int stackNo;
		STACK_DATA_TYPE *turbo;
		VectorStack vs;
	public:
		/** Do not use this unless you are not acessing the stack at all - results in invalid stack! */
		TurboStack() : turbo(nullptr), stackNo(0) { }
		/** Create a turbo-stack using the given shared turbo area and stack-number */
		TurboStack(STACK_DATA_TYPE *turboo, int stackNoo) : turbo(turboo), stackNo(stackNoo) { }

		/** Helper function for indexing in the "turbo" array */
		static constexpr int turboIndex(int stackNo, int stackDepth) {
			return (stackNo * STACK_TURBO_DEPTH * sizeof(STACK_DATA_TYPE))
				+ (stackDepth * sizeof(STACK_DATA_TYPE));
		}

		/** Helper function to determine the size of the turbo-area */
		static constexpr std::size_t turboSize() {
			return STACK_TURBO_DEPTH * sizeof(STACK_DATA_TYPE) * STACK_BREADTH;
		}

		/** The size of this stack is the size of the underlying vector */
		std::size_t size() const override {
			return stackSize;
		}

		/** Gets the ith element of the stack - where index 0 is the top and 1 is the second elem. */
		const STACK_DATA_TYPE& operator[](std::size_t i) const override {
			if(i < STACK_TURBO_DEPTH) {
				// The first few elements are stored in the cache-friendly area
				return turbo[turboIndex(stackNo, i)];
			} else {
				// The other elements are in usual vectorstacks
				return vs[i - STACK_TURBO_DEPTH];
			}
		}

		/** Push copy of the given elem on top of the stack */
		void push(STACK_DATA_TYPE elem) override {
			if(stackSize < STACK_TURBO_DEPTH) {
				LOGT("PUSH-TURBO");
				// If there is still place for that, use directly the cache-friendly area
				turbo[turboIndex(stackNo, stackSize)] = elem;
			} else {
				// Just use the underlying VectorStack
				vs.push(elem);
			}
			++stackSize;
		}

		/** Get the top element of the stack and shrink the stack */
		STACK_DATA_TYPE pop() override {
			if(stackSize <= STACK_TURBO_DEPTH) {
				LOGT("POP-TURBO");
				// Simple case, just pop from the small cache
				return turbo[turboIndex(stackNo, --stackSize)];
			} else {
				// Use the underlying vector stack...
				STACK_DATA_TYPE dt = vs.pop();
				--stackSize;
				return dt;
			}
		}
	};

	/**
	 * A hashing data structure. It contains 8 stacks directly for fast access and 8 possible extension 'slots'.
	 * This multi-stack data structure handle any number of stacks with bigger indexes of the stacks being the
	 * slower and having more and more indirection in case of an access. The indirection is handled by vectors of
	 * vectors to other stacks (see 'slow'). Also aside these, there is a 'turbo' array to support shallow stacks.
	 * So this data structure is able to grow indefinately both horizontally and vertically as in both the number
	 * of stacks and the depth of these stacks are theorethically unlimited (until OOM). Also accessing stacks
	 * that are having a very big index does not grow the memory requirements indefinately because we use caching.
	 */
	class HashStacks {
		// Place for the 'turbo' data - cache optimized to fit closely to each other when used
		// or: the first few levels of the fast-breath number of stacks...
		STACK_DATA_TYPE turbo[TurboStack::turboSize()];
		TurboStack turboStacks[STACK_BREADTH];

		// Extension slots - contains the other stacks (hashed into this multi-map)
		// find(..) returns an iterator in this case!
		std::unordered_map<std::size_t, VectorStack> slots;

	public:
		/** Create an empty multi-stack */
		HashStacks() {
			// Initialize the fast access stacks
			for(int i = 0; i < STACK_BREADTH; ++i) {
				turboStacks[i] = TurboStack(turbo, i);
			}
			// slow(er)-access extension slots stay empty
		}

		inline MultiStack::Stack& operator[] (std::size_t i) {
			if(i < STACK_BREADTH) {
				// First STACK_BREADTH stacks are of fast direct access with turbo
				return turboStacks[i];
			} else {
				// TODO: Do some "GC-ing" in the case of slots and buckets 
				// Rem.: Not as bad as you might think: pops should at least handle things normally!

				// Every index other than the first breadth are going to get hashed...
				std::size_t slotIndex = (i - STACK_BREADTH);
				// This default constructs if it does not find the stack already!
				return slots[slotIndex];
			}
		}
	};
}
#endif // HASH_STACKS_H
