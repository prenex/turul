// This could be in the header, but wanted to show how cpps work
#include "ComponentImpl.h"

namespace SimpleAdderServiceImpl {
	int ComponentImpl::add(int x, int y) {
		return x + y;
	}
}
