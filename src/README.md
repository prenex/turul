# Turul-core

This is the core of the Turul metaprogramming environment implemented in C++14 using my LightWeightComponents design-pattern / approach for modern, component based development in C++. We have designed the application with this system as it provides very lightweight dependency injection and easy customization of the system even in the core, C++ side to it. Also it gives a very structured approach so that the code-base and architecture will be easily understood even if will grow to be a big system with time. Hopefully however it will not grow unnecessarily big. Because of the interface-based dependency injection schemes it is really easy to provide your own optimized implementations for the components while keeping the whole system running - or to make a sophisticated GUI editor and such things instead of the terminal interface provided as a default.

There is no complicated framework for the dependency injection and component-interface based programming in C++, but everything is expressed in clever code that should be easy to understand for anyone. Still I have copied the description of the system from its own git page so that it will be clear what version we are using and how it is applied. Before trying to send pull requests and such things please read these chapters so the architecture stays clean while cooperating.

TODO: Remove text that is too generic for us and update architecture.

# LightWeightComponents faq
Light-weight component patterns for C++. Like a framework that is able to do DI, but sucks less so much that it didn't became a framework at all in the end lol :-)

Because there is no "real" framework. The system comes with a self-contained small example calculator which should be big enough to understand how to use the presented ideas, but small enough to immediately refactor to your own needs.

Details:
========
A really small example that shows a good pattern in component based C++ programming. First I wanted to make a framework that is able to do dependency injection like things but is suckless and came up with the idea to express more in plain code than that. This is the result which can be used for building plugin-based architectures while keeping the static linkage and easy usage. This enables 3rd party developers to easily add code to your codebase while having a clean structure. Also this enables something that looks like a sane dependency injection without any weird "annotation" but keeping a very clean code.

Architecture:
=============

	.
	├── components
	│   ├── AdderService.h
	│   ├── FilePrinterServiceImpl
	│   │   ├── ComponentImpl.cpp
	│   │   ├── ComponentImpl.h
	│   │   ├── ComponentImpl.o
	│   │   └── node.mk
	│   ├── MainControllerService.h
	│   ├── MainControllerServiceImpl
	│   │   ├── ComponentImpl.cpp
	│   │   ├── ComponentImpl.h
	│   │   ├── ComponentImpl.o
	│   │   └── node.mk
	│   ├── main.cpp
	│   ├── main.o
	│   ├── node.mk
	│   ├── PrinterServices.h
	│   ├── SimpleAdderServiceImpl
	│   │   ├── ComponentImpl.cpp
	│   │   ├── ComponentImpl.h
	│   │   ├── ComponentImpl.o
	│   │   └── node.mk
	│   └── SimplePrinterServiceImpl
	│       └── ComponentImpl.h
	├── LICENSE
	├── main
	├── makefile
	├── out.txt
	├── README.md
	└── traverse.mk

* The main file should not contain anything else just the interfacing modules and implementation components and the main calling a controller...
* Interfacing module: this is a header of a class that the implementers implement. Its code just delegates to the real implementers.
* The way of delegation (1:1 or 1:n and exception handling etc) can be seen in the code of the interfacing module directly!
* Implementation module: this is a directory with a header file of the implementation. The cpp for the header has the main entry, but there can be a lot of "normal" files and classes below this directory that belongs to the public interface named ComponentImpl.
* Dependency Injection-like things can be done by just creating the interfacing module class. That is all!

I have added a non-recursive make that enables one to build *.cpp files and directory structures below component implementation directories. The interfacing headers are on the top level as there should be only 10-50 components in a real application at most and their details should be hidden below their implementation directories. There should be a componentImpl.h and cpp for each and those can use DI easily, but other than that you can create your own structures in the implementation modules.

* The make 'system' uses node.mk files in directories.
* These describe the *.o files created in that directory and further subdirectories
* You can also specify *.a libs at these points.
* In the components directory, you need to fill the top level node.mk for the impl modules. The modules should have cpp files and node.mk files but here I have shown some examples that are header-only and really lightweight. That is also a way to go.
* Interfacing headers need not use any namespaces (though not prohibited), but each implementation component should do this to avoid name clashes!

For an even simpler architecture without the descending non-recursive make, look at the earlier git commits if you want, but that is only for really small projects. See: eb460b2d58f5e8561ec91e7d4e5162a3d5e874ad

Actually this can be used in that way that the whole "system" starts later than the main at a random point. I hope you see how.
So this is kind of a static module/plugin system or pattern where instead of knowing what this or that "container" do, you see everything explained in code. This should make it easier to grasp the things even for those who don't know these techniques and hopefully the whole approach is more cleaner than its heavyweight counterparts.

Highlights
==========

Dependency injection in an implementer:


	#ifndef MAIN_CONTROLLER_SERVICE_IMPL_H
	#define MAIN_CONTROLLER_SERVICE_IMPL_H
	
	#include "../AdderService.h"
	#include "../PrinterServices.h"
	#include "../MainControllerService.h"
	
	namespace MainControllerServiceImpl {
		class ComponentImpl : public MainControllerService {
		private:
			AdderService adder; // DI !!!
			PrinterServices printers; // DI !!!
		public:
			ComponentImpl() {
				MainControllerService::registerMainControllerService(this);
			}
			virtual int run();
		};
	}
	// Creating the implementation ensures service reg.
	// this will be included before the main, and run before that!
	#ifdef LWC_IMPLEMENTATION_MODULES
	static MainControllerServiceImpl::ComponentImpl mainControllerServiceImpl;
	#endif
	
	#endif

In the cpp file you can just use the variables that will serve the implementation chosen by the main:

	int result = adder.add(5, 10);
	printers.print(result);

In the main.cpp one can define declaratively what interfacing headers and implementation components the deployment uses and what is the entry point. It is like some 'descriptor' files in heavyweight systems:

	#define LWC_INTERFACING_MODULES
	#include "AdderService.h"
	#include "PrinterServices.h"
	#include "MainControllerService.h"
	
	// There can be multiple printer services (see interfacing module)
	// Here we have two of them (one writes to stdout and other to file)
	#define LWC_IMPLEMENTATION_MODULES
	#include "SimpleAdderServiceImpl/ComponentImpl.h"
	#include "SimplePrinterServiceImpl/ComponentImpl.h"
	#include "FilePrinterServiceImpl/ComponentImpl.h"
	#include "MainControllerServiceImpl/ComponentImpl.h"
	
	int main() {
		// Run the entry service
		MainControllerService mainControllerService;
		return mainControllerService.run();
	}

Descending non-recursive make build uses small and clean *.mk descriptions like this:

	# Component make descriptor
	# -------------------------
	#
	# List all implementation subdirectories with node.mk files in them
	SUBDIRS-y += 
	# List all *.o files in the top level directory of the component
	OBJS-y    += ComponentImpl.o
	# List all library (*.a) files here if necessary
	LIBS-y    +=
