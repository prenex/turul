# Architectural overview

This document discuss the main architecture of the system as a standalone, library or IDE.

TODO: Currently only the standalone architecture is presented as that is the first I will work out.

Component architecture in the standalone case
=============================================

                              <<entry point>>
                          <<describes components>>
	                        ┌─────────┐
	                        │turul.cpp│
	                        └────┬────┘
	                             │
	                     ┌───────┴─────────┐
	                     │ControllerService│
	                     └───────┬─────────┘
	                             │ (implements)
	                ┌────────────┴──────────────────┐
	       ┌────────┤StandaloneControllerServiceImpl│
	       │        └────────────┬──────────────────┘
	       │                     │
	       │             ┌───────┴────────┐
	       │             │TurulCoreService│
	       │             └───────┬────────┘
	       │                     │ (implements)
	       │           ┌─────────┴──────────┐   has   ┌────────────┐
	       ├───────────┤TurulCoreServiceImpl├─────────┤StackHandler│
	       │           └───────┬────┬───────┘         └────────────┘
	       │                   │    └──────────┐         <<class>>
	       │                   │               │
	┌──────┴───────┐ ┌─────────┴────────┐ ┌────┴────────┐make┌────────┐
	│LoggerServices│ │DictionaryServices│ │  IoService  ├────┤TreeHead│
	└────┬─────────┘ └─────────────┬────┘ └──────────┬──┘updt└────────┘
	     │     (implements)        │  (implements)   │        <<class>>
	┌────┴──────┐ ┌────────────────┴────────┐  ┌─────┴───────────┐
	│StdLogger  │ │BootDictionaryServiceImpl│  │TBufIoServiceImpl│
	│ServiceImpl│ └─────────────────────────┘  └────────┬────────┘
	└───────────┘                                 ┌─────┴─────┐
	                                          ┌───┴──┐ use ┌──┴──┐
	                                          │tbuf.h├────>│fio.h│
	                                          └──────┘     └─────┘

Logical component grouping
==========================

We can group the components into the following logical groups:

* Entry point and setup
* turul\_standalone
* turul\_core
* turul\_words
* lwc\_log

Also as you can see we use things from:

* tbuf and fio header only libraries

These logical groups are not expressed in code directly but presented here to ease understanding even more for _common_ use cases.

Entry point and setup
---------------------

* This contains turul.cpp as the entry point for having the command line stand-alone executable "turul".
* Might have things from the component framework maybe but should not have component code.
* Contains the ControllerService and its implementations (here StandaloneControllerServiceImpl).

turul\_core
----------

Contains:

* TurulCoreService
* TurulCoreServiceImpl
* StackHandler class
* IoService
* TBufIoServiceImpl
* TreeHead class

This should be enough to use Turul as a library for basic use cases and contains the engine, but does not contain any predefined words. The IoService is implemented with files in this case, but that is a point in the architecture where we can introduce network / client-server models into the system by providing networked implementations.

turul\_words
-----------

Contains:

* DictionaryServices for providing interface to add semantics to words
* BootDictionaryService for bootstraping a forth-like language

If you are extending the system by defining meaning of words in C++, your component belongs to this logical group. Please create it to adhere the DictionaryServices interfacing module. That way your C++ parsing words will be automatically called by the system when semantic run is going on.

This is here just to add "native" words and we provide this so that optimizations are possible. If you are not providing dictionary name, you are extending (not overriding) the default dictionary - that is: the words you can access when you import/use nothing. When you are providing an optimized native word for your compiler or system, you should know that native words always have prefernce over Turul-words! Because of this, you can provide both the Turul and optimized native implementations for your system if necessary in case someone might not want to recompile their turul for getting your native optimizations...

lwc\_log
--------

This is basically the simple logging infrastructure provided in LightWeightComponents. StdLoggerServiceImpl uses stdout and stderr here.

tbuf and fio
------------

These are so-called header-only libraries that are able to parse the trees used as the file-based representation. Aside that, fio provides generic and fast input-output for us.
