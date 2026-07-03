#include <numeric>

#include "MovingAverageStrategy.h"

MovingAverageStrategy::MovingAverageStrategy(size_t period) : period(period) {
}

bool MovingAverageStrategy::shouldBuy(const std::vector<int>& price_history) const {
	if (price_history.size() <= period) return false;

	std::vector<int> previous_prices(price_history.begin(), price_history.end() - 1);
	double average = movingAverage(previous_prices);
	int current_price = price_history.back();

	return current_price > average;
}

bool MovingAverageStrategy::shouldSell(const std::vector<int>& price_history) const {
	if (price_history.size() <= period) return false;

	std::vector<int> previous_prices(price_history.begin(), price_history.end() - 1);
	double average = movingAverage(previous_prices);
	int current_price = price_history.back();

	return current_price < average;
}

double MovingAverageStrategy::movingAverage(const std::vector<int>& price_history) const {
	size_t count = price_history.size() < period ? price_history.size() : period;
	int sum = std::accumulate(price_history.end() - count, price_history.end(), 0);
	return static_cast<double>(sum) / count;
}
