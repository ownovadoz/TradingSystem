#pragma once
#include <gmock/gmock.h>
#include "i_stock_broker_driver.h"

class MockStockDriver : public IStockBrokerDriver {
public:
	MOCK_METHOD(void, login, (const std::string& id, const std::string& password), (override));
	MOCK_METHOD(void, buy, (const std::string& stock_code, int price, int count), (override));
	MOCK_METHOD(void, sell, (const std::string& stock_code, int price, int count), (override));
	MOCK_METHOD(int, getPrice, (const std::string& stock_code), (override));
};
