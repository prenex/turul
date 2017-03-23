#ifndef BOOT_DICTIONARY_SERVICE_IMPL_H
#define BOOT_DICTIONARY_SERVICE_IMPL_H

#include "../DictionaryServices.h"

namespace BootDictionaryServiceImpl {
	class ComponentImpl : public DictionaryServices {
	public:
		ComponentImpl() {
			DictionaryServices::registerImpl(this);
		}
		virtual int test();
	};
}
// Creating the implementation ensures service reg.
// this will be included before the main, and run before that!
#ifdef LWC_IMPLEMENTATION_MODULES
static BootDictionaryServiceImpl::ComponentImpl bootDictionaryServiceImpl;
#endif

#endif // BOOT_DICTIONARY_SERVICE_IMPL_H
