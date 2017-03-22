# Architectural overview

This document discuss the main architecture of the system as a standalone, library or IDE.

TODO: Currently only the standalone architecture is presented as that is the first I will work out.

Component architecture in the standalone case
=============================================

	                        ┌─────────┐
	                        │turul.cpp│
	                        └────┬────┘
	                             │
	                             │
	                ┌────────────┴───────────────────┐
	       ┌────────┤StandaloneControllerServiceImpl*│
	       │        └────────────┬───────────────────┘
	       │                     │
	       │                     │
	       │             ┌───────┴─────────────┐   has   ┌────────────┐
	       ├─────────────┤TurulCoreServiceImpl*├─────────┤StackHandler│
	       │             └───────┬────┬────────┘         └────────────┘
	       │                     │    └──────────┐         <<class>>
	       │                     │               │
	┌──────┴───────┐ ┌───────────┴──────┐ ┌──────┴───────────┐has ┌────────┐
	│LoggerServices│ │DictionaryServices│ │TBufIoServiceImpl*├────┤TreeHead│
	└────┬─────────┘ └─────────────┬────┘ └─────────────┬────┘    └────────┘
	     │     (implements)        │              ┌─────┴─────┐    <<class>>
	┌────┴──────┐ ┌────────────────┴────────┐ ┌───┴──┐     ┌──┴──┐
	│StdLogger  │ │BootDictionaryServiceImpl│ │tbuf.h├────>│fio.h│
	│ServiceImpl│ └─────────────────────────┘ └──────┘     └─────┘
	└───────────┘
Rem.: Service implementations marked with asterisk (\*) have interfaces too, but not shown here for simplicity.

NameSpace breakdown
===================

We have the following namespaces:

* code without namespace
* turul\_core
* turul\_words
* lwc\_log

Also as you can see we use things from:

* tbuf and fio namespaces

Code without a namespace
------------------------

* This contains turul.cpp as the entry point for having the command line stand-alone executable "turul".
* Might have things from the component framework maybe but should not have component code.

turul\_core
----------

Contains:

* TurulCoreService and implementation
* StackHandler class
* TBufIoService and implementation
* TreeHead class

This should be enough to use Turul as a library for basic use cases and contains the engine, but does not contain any predefined words.

turul\_words
-----------

Contains:

* DictionaryServices for providing interface to add semantics to words
* BootDictionaryService for bootstraping a forth-like language

If you are extending the system by defining meaning of words in C++, put your component in this namespace and create it to adhere the DictionaryServices interfacing module. That way your C++ parsing words will be automatically called by the system when semantic run is going.

This is here just to add "native" words and we provide this so that optimizations are possible. If you are not providing dictionary name, you are extending (not overriding) the default dictionary - that is: the words you can access when you import/use nothing. When you are providing an optimized native word for your compiler or system, you should know that native words always have prefernce over Turul-words! Because of this, you can provide both the Turul and optimized native implementations for your system if necessary.

lwc\_log
--------

This is basically the simple logging infrastructure provided in LightWeightComponents. StdLoggerServiceImpl uses stdout and stderr here.

tbuf and fio
------------

These are so-called header-only libraries that are able to parse the trees used as the file-based representation.
