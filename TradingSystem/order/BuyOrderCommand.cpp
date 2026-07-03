#include "BuyOrderCommand.h"

BuyOrderCommand::BuyOrderCommand(IStockBrokerDriver& driver, const std::string& stock_code, int price, int count)
	: driver(driver), stock_code(stock_code), price(price), count(count) {
}

void BuyOrderCommand::execute() {
	driver.buy(stock_code, price, count);
}

std::string BuyOrderCommand::description() const {
	return "BUY " + stock_code + " x" + std::to_string(count) + " @" + std::to_string(price);
}
