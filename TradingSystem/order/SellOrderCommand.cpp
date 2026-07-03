#include "SellOrderCommand.h"

SellOrderCommand::SellOrderCommand(IStockBrokerDriver& driver, const std::string& stock_code, int price, int count)
	: driver(driver), stock_code(stock_code), price(price), count(count) {
}

void SellOrderCommand::execute() {
	driver.sell(stock_code, price, count);
}

std::string SellOrderCommand::description() const {
	return "SELL " + stock_code + " x" + std::to_string(count) + " @" + std::to_string(price);
}
