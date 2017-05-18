#ifndef MULTI_STACK_HANDLER_SERVICE_H
#define MULTI_STACK_HANDLER_SERVICE_H

#include<cstdlib>	// for size_t

// Lets you override the data type of the stack when necessary...
#ifndef STACK_DATA_TYPE
// Otherwise use size_t as we need to hold pointers of course in most cases...
#define STACK_DATA_TYPE std::size_t
#endif // STACK_DATA_TYPE

/** Just a forward declaration */
class Stack;

/**
 * Provides a multi-stack with its operations
 */
class MultiStackService {
private:
	// Service implementation
	static MultiStackService *serviceImpl;
protected:	
	static void registerImpl(MultiStackService* impl) {
		serviceImpl = impl;
	}
public:
	virtual bool test() const {
		if(serviceImpl != nullptr) {
			return serviceImpl->test();
		}
	}

	/** Gets the ith stack - reference ownership is NOT transferred! */
	virtual Stack& operator[] (std::size_t i) {
		return serviceImpl->operator[](i);
	}
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

// The variable should be defined in some cpp file
// it will be in the cpp that set this!
#ifdef LWC_INTERFACING_MODULES
MultiStackService *MultiStackService::serviceImpl;
#endif

#endif // MULTI_STACK_HANDLER_SERVICE_H
