#include "auto_trading_system.h"

void AutoTradingSystem::selectStockBroker(std::unique_ptr<IStockBrokerDriver> driver) {
	driver = std::move(driver);
}

void AutoTradingSystem::login(const std::string& id, const std::string& password) {

}

void AutoTradingSystem::buy(const std::string& stockCode, int price, int count) {

}

void AutoTradingSystem::sell(const std::string& stockCode, int price, int count) {

}

int AutoTradingSystem::getPrice(const std::string& stockCode) {

}

void AutoTradingSystem::buyNiceTiming(const std::string& stockCode, int totalMoney) {

}

void AutoTradingSystem::sellNiceTiming(const std::string& stockCode, int count) {

}

