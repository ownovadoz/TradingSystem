#pragma once
#include <string>

class IStockBrokerDriver {
public:
	virtual ~IStockBrokerDriver() = default;

	virtual void login(const std::string& id, const std::string& password) = 0;
	virtual void buy(const std::string& stock_code, int price, int count) = 0;
	virtual void sell(const std::string& stock_code, int price, int count) = 0;
	virtual int getPrice(const std::string& stock_code) = 0;
};

