#ifndef TBUF_IO_SERVICE_IMPL_H
#define TBUF_IO_SERVICE_IMPL_H

#include "../IoService.h"
namespace TBufIoServiceImpl {
	class ComponentImpl : public IoService {

		// TODO: we should have a double-buffered operation mode - and maybe manipulation possibilities for multiple trees too?
	
	public:
		ComponentImpl() {
			IoService::registerImpl(this);
		}
		virtual bool testService();
	};
} // end namespace

// Creating the implementation ensures service reg.
// this will be included before the main, and run before that!
#ifdef LWC_IMPLEMENTATION_MODULES
static TBufIoServiceImpl::ComponentImpl serviceImpl;
#endif

#endif // TBUF_IO_SERVICE_IMPL_H
