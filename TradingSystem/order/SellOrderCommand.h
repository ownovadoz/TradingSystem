#pragma once
#include <string>

#include "IOrderCommand.h"
#include "../driver/i_stock_broker_driver.h"

class SellOrderCommand : public IOrderCommand {
public:
	SellOrderCommand(IStockBrokerDriver& driver, const std::string& stock_code, int price, int count);

	void execute() override;
	std::string description() const override;

private:
	IStockBrokerDriver& driver;
	std::string stock_code;
	int price;
	int count;
};
