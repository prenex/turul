#ifndef DICTIONARY_SERVICES_H
#define DICTIONARY_SERVICES_H

#include<vector>

// Interfacing module's class
// ends with 's' (plural) as there can be multiple implementations!
class DictionaryServices {
private:
	static std::vector<DictionaryServices*> serviceImpls;
public:
	/** Return the number of implementations */
	virtual int test() {
		// Count implementations
		int implCount = 0;
		for(DictionaryServices* ds : serviceImpls) {
			implCount += ds->test();
		}
		// Return the aggregated count
		return implCount;
	}
	
	static void registerImpl(DictionaryServices* impl) {
		serviceImpls.push_back(impl);
	}
};

// The variable should be defined in some cpp file
// it will be in the cpp that set this!
#ifdef LWC_INTERFACING_MODULES
std::vector<DictionaryServices*> DictionaryServices::serviceImpls;
#endif

#endif // DICTIONARY_SERVICES_H
