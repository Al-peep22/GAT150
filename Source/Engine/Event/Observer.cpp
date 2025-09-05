#include "Observer.h"

namespace viper {
	IObserver::~IObserver() {
		OBSERVER_REMOVE_SELF;
	}
}