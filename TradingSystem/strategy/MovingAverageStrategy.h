#pragma once
#include <cstddef>
#include <vector>

#include "ITimingStrategy.h"

class MovingAverageStrategy : public ITimingStrategy {
public:
	explicit MovingAverageStrategy(size_t period = 3);

	bool shouldBuy(const std::vector<int>& price_history) const override;
	bool shouldSell(const std::vector<int>& price_history) const override;

private:
	double movingAverage(const std::vector<int>& price_history) const;

	size_t period;
};
