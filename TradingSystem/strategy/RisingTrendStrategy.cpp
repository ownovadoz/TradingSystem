#include "RisingTrendStrategy.h"

bool RisingTrendStrategy::shouldBuy(const std::vector<int>& price_history) const {
	if (price_history.size() < 2) return false;

	for (size_t i = 0; i < price_history.size() - 1; ++i) {
		if (price_history[i] >= price_history[i + 1]) {
			return false;
		}
	}
	return true;
}

bool RisingTrendStrategy::shouldSell(const std::vector<int>& price_history) const {
	if (price_history.size() < 2) return false;

	for (size_t i = 0; i < price_history.size() - 1; ++i) {
		if (price_history[i] <= price_history[i + 1]) {
			return false;
		}
	}
	return true;
}
