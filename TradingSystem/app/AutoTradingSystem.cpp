#include <vector>
#include <thread>
#include <chrono>

#include "AutoTradingSystem.h"
#include "strategy/RisingTrendStrategy.h"

AutoTradingSystem::AutoTradingSystem(std::unique_ptr<IStockDriverFactory> factory,
	std::unique_ptr<ITimingStrategy> strategy)
	: factory(std::move(factory)),
	strategy(strategy ? std::move(strategy) : std::make_unique<RisingTrendStrategy>()) {
}

void AutoTradingSystem::selectStockBroker(std::unique_ptr<IStockBrokerDriver> driver) {
	this->driver = std::move(driver);
}

void AutoTradingSystem::selectStockBroker(BrokerType type) {
	selectStockBroker(factory->create(type));
}

void AutoTradingSystem::setTimingStrategy(std::unique_ptr<ITimingStrategy> strategy) {
	this->strategy = std::move(strategy);
}

void AutoTradingSystem::login(const std::string& id, const std::string& password) {
	if (!driver) {
		throw BrokerNotSelectedException();
	}

	driver->login(id, password);
	authorized = true;
}

void AutoTradingSystem::buy(const std::string& stock_code, int price, int count) {
	if (!driver) {
		throw BrokerNotSelectedException();
	}
	if (!authorized)
		throw NotAuthorizedException();
	if (driver) driver->buy(stock_code, price, count);
}

void AutoTradingSystem::sell(const std::string& stock_code, int price, int count) {
	if (!driver) {
		throw BrokerNotSelectedException();
	}
	if (!authorized)
		throw NotAuthorizedException();

	if (driver) driver->sell(stock_code, price, count);
}

int AutoTradingSystem::getPrice(const std::string& stock_code) {
	if (!driver) {
		throw BrokerNotSelectedException();
	}
	if (driver) return driver->getPrice(stock_code);
	return 0;
}

void AutoTradingSystem::buyNiceTiming(const std::string& stock_code, int total_money) {
	if (!driver) {
		throw BrokerNotSelectedException();
	}

	if (!authorized)
		throw NotAuthorizedException();

	std::vector<int> prices = collectPriceTrend(stock_code);

	if (strategy->shouldBuy(prices)) {
		int current_price = prices.back();
		int shareCount = calculateMaxShares(total_money, current_price);
		if (shareCount > 0) {
			driver->buy(stock_code, current_price, shareCount);
		}
	}
}

void AutoTradingSystem::sellNiceTiming(const std::string& stock_code, int count) {
	if (!driver) return;
	if (!authorized)
		throw NotAuthorizedException();
	std::vector<int> prices = collectPriceTrend(stock_code);

	if (strategy->shouldSell(prices)) {
		driver->sell(stock_code, prices.back(), count);
	}
}

bool AutoTradingSystem::isAuthorized() {
	return authorized;
}

int AutoTradingSystem::calculateMaxShares(int total_money, int current_price) const {
	if (current_price <= 0) return 0;
	return total_money / current_price;
}

std::vector<int> AutoTradingSystem::collectPriceTrend(const std::string& stock_code) {
	std::vector<int> prices(TREND_CHECK_COUNT);
	for (int i = 0; i < TREND_CHECK_COUNT; ++i) {
		prices[i] = driver->getPrice(stock_code);
		if (i < TREND_CHECK_COUNT - 1) {
			std::this_thread::sleep_for(PRICE_CHECK_INTERVAL);
		}
	}
	return prices;
}