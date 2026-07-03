#include <algorithm>

#include "BreakoutStrategy.h"

BreakoutStrategy::BreakoutStrategy(size_t lookback_count) : lookback_count(lookback_count) {
}

bool BreakoutStrategy::shouldBuy(const std::vector<int>& price_history) const {
	if (price_history.size() <= lookback_count) return false;

	auto previous_begin = price_history.end() - lookback_count - 1;
	auto previous_end = price_history.end() - 1;
	int highest_price = *std::max_element(previous_begin, previous_end);
	int current_price = price_history.back();

	return current_price > highest_price;
}

bool BreakoutStrategy::shouldSell(const std::vector<int>& price_history) const {
	if (price_history.size() <= lookback_count) return false;

	auto previous_begin = price_history.end() - lookback_count - 1;
	auto previous_end = price_history.end() - 1;
	int lowest_price = *std::min_element(previous_begin, previous_end);
	int current_price = price_history.back();

	return current_price < lowest_price;
}
