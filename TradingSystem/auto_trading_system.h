#pragma once
#include <memory>
#include <string>
#include <vector>

class AutoTradingSystem {
public:
	void selectStockBroker(std::unique_ptr<IStockBrokerDriver> driver);

	void login(const std::string& id, const std::string& password);

	void buy(const std::string& stockCode, int price, int count);
	void sell(const std::string& stockCode, int price, int count);
	int getPrice(const std::string& stockCode);

	void buyNiceTiming(const std::string& stockCode, int totalMoney);
	void sellNiceTiming(const std::string& stockCode, int count);

private:
	std::unique_ptr<IStockBrokerDriver> driver;
};
