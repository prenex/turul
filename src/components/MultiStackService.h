#ifndef MULTI_STACK_SERVICE_H
#define MULTI_STACK_SERVICE_H

#include<cstdlib>	// for size_t

// Lets you override the data type of the stack when necessary...
#ifndef STACK_DATA_TYPE
// Otherwise use size_t as we need to hold pointers of course in most cases...
#define STACK_DATA_TYPE std::size_t
#endif // STACK_DATA_TYPE

namespace MultiStack {

/** Just a forward declaration - a single(nonmulti)-stack */
class Stack;

/**
 * Provides a multi-stack service with its operations
 */
class Service {
public:
	virtual bool test() const = 0;

	/** Stash away the top elem of the ith stack to the stash-stack */
	virtual void nstash(std::size_t i, std::size_t n) = 0;

	/** Pushes an elem to the ith stach from the top of the stash-away stack */
	virtual void nunstash(std::size_t i, std::size_t n) = 0;

	/** Stash away the top elem of the ith stack to the stash-stack */
	virtual void stash(std::size_t i) = 0;

	/** Pushes an elem to the ith stach from the top of the stash-away stack */
	virtual void unstash(std::size_t i) = 0;

	/** Gets the ith stack - reference ownership is NOT transferred! */
	virtual Stack& operator[] (std::size_t i) = 0;
};

/** Abstract superclass for an individual stack */
class Stack {
public:
	/** The size of this stack */
	virtual std::size_t size() const = 0;
	/** Gets the ith element of the stack - where index 0 is the top and 1 is the second elem. */
	virtual const STACK_DATA_TYPE& operator[](std::size_t i) const = 0;
	/** Gets the top element of the stack */
	virtual const STACK_DATA_TYPE& top() const {
		return (*this)[0];
	}

	/** Push copy of the given elem on top of the stack */
	virtual void push(STACK_DATA_TYPE elem) = 0;

	/** Get the top element of the stack and shrink the stack */
	virtual STACK_DATA_TYPE pop() = 0;
};

// Here you might have DTO structs and stuff to interface to us...

} // MultiStack namespace

#endif // MULTI_STACK_SERVICE_H
