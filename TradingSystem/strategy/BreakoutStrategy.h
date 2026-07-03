#pragma once
#include <cstddef>
#include <vector>

#include "ITimingStrategy.h"

class BreakoutStrategy : public ITimingStrategy {
public:
	explicit BreakoutStrategy(size_t lookback_count = 3);

	bool shouldBuy(const std::vector<int>& price_history) const override;
	bool shouldSell(const std::vector<int>& price_history) const override;

private:
	size_t lookback_count;
};
