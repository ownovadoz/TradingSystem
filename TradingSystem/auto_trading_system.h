#pragma once
#include "i_stock_broker_driver.h"
#include "i_stock_driver_factory.h"
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class BrokerNotSelectedException : public std::logic_error {
public:
	BrokerNotSelectedException() : std::logic_error("Please select a stock broker. ") {}
};

class NotAuthorizedException : public std::logic_error {
public:
	NotAuthorizedException() : std::logic_error("Please login first.") {}
};

class AutoTradingSystem {
public:
	explicit AutoTradingSystem(std::unique_ptr<IStockDriverFactory> factory = nullptr);

	void selectStockBroker(std::unique_ptr<IStockBrokerDriver> driver);
	void selectStockBroker(BrokerType type);

	void login(const std::string& id, const std::string& password);

	void buy(const std::string& stock_code, int price, int count);
	void sell(const std::string& stock_code, int price, int count);
	int getPrice(const std::string& stock_code);

	void buyNiceTiming(const std::string& stock_code, int total_money);
	void sellNiceTiming(const std::string& stock_code, int count);
	bool isAuthorized();

private:
	std::unique_ptr<IStockDriverFactory> factory;
	std::unique_ptr<IStockBrokerDriver> driver;
	bool authorized = false;
};
