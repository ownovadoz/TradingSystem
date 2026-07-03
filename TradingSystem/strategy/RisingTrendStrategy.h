#pragma once
#include <vector>

#include "ITimingStrategy.h"

class RisingTrendStrategy : public ITimingStrategy {
public:
	bool shouldBuy(const std::vector<int>& price_history) const override;
	bool shouldSell(const std::vector<int>& price_history) const override;
};
