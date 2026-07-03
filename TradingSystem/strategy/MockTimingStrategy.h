#pragma once
#include <vector>

#include <gmock/gmock.h>

#include "ITimingStrategy.h"

class MockTimingStrategy : public ITimingStrategy {
public:
	MOCK_METHOD(bool, shouldBuy, (const std::vector<int>& price_history), (const, override));
	MOCK_METHOD(bool, shouldSell, (const std::vector<int>& price_history), (const, override));
};
