#pragma once
#include <memory>
#include "i_stock_broker_driver.h"

enum class BrokerType {
	Kiwer,
	Nemo
};

class IStockDriverFactory {
public:
	virtual ~IStockDriverFactory() = default;
	virtual std::unique_ptr<IStockBrokerDriver> create(BrokerType type) const = 0;
};

