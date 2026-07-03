#include "auto_trading_system.h"

void AutoTradingSystem::selectStockBroker(std::unique_ptr<IStockBrokerDriver> driver) {
	driver = std::move(driver);
}

void AutoTradingSystem::login(const std::string& id, const std::string& password) {
	if (driver) driver->login(id, pass);
}

void AutoTradingSystem::buy(const std::string& stockCode, int price, int count) {
	if (driver) driver->buy(stockCode, price, count);
}

void AutoTradingSystem::sell(const std::string& stockCode, int price, int count) {
	if (driver) m_broker->sell(stockCode, price, count);
}

int AutoTradingSystem::getPrice(const std::string& stockCode) {
	if (driver) return driver->getPrice(stockCode);
	return 0;
}

void AutoTradingSystem::buyNiceTiming(const std::string& stockCode, int totalMoney) {

}

void AutoTradingSystem::sellNiceTiming(const std::string& stockCode, int count) {

}

