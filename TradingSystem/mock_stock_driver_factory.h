#pragma once
#include <gmock/gmock.h>
#include "i_stock_broker_driver.h"
#include "i_stock_driver_factory.h"

class MockStockDriverFactory : public IStockDriverFactory {
public:
	MOCK_METHOD(std::unique_ptr<IStockBrokerDriver>, create, (BrokerType type), (const, override));
};
