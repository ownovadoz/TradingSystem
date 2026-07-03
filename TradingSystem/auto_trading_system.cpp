#include "auto_trading_system.h"

AutoTradingSystem::AutoTradingSystem(std::unique_ptr<IStockDriverFactory> factory)
	: factory(std::move(factory)) {
}

void AutoTradingSystem::selectStockBroker(std::unique_ptr<IStockBrokerDriver> driver) {
	this->driver = std::move(driver);
}

void AutoTradingSystem::selectStockBroker(BrokerType type) {
	selectStockBroker(factory->create(type));
}

void AutoTradingSystem::login(const std::string& id, const std::string& password) {
	if (!driver) {
		throw BrokerNotSelectedException();
	}

	driver->login(id, password);
	authorized = true;
}

void AutoTradingSystem::buy(const std::string& stock_code, int price, int count) {

}

void AutoTradingSystem::sell(const std::string& stock_code, int price, int count) {

}

int AutoTradingSystem::getPrice(const std::string& stock_code) {
	return 0;
}

void AutoTradingSystem::buyNiceTiming(const std::string& stock_code, int total_money) {

}

void AutoTradingSystem::sellNiceTiming(const std::string& stock_code, int count) {

}

bool AutoTradingSystem::isAuthorized() {
	return authorized;
}
