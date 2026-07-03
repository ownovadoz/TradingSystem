#include "IStockBrockerDriver.h"
#include "kiwer_api.cpp"

using std::string;

class KiwerStockDriver : public IStockBrockerDriver {
private:
	KiwerAPI kiwer_api;

public:
	void login(const string& id, const string& pass) override {
		kiwer_api.login(id, pass);
	}

	void buy(const string& stockCode, int price, int count) override {
		kiwer_api.buy(stockCode, count, price);
	}

	void sell(const string& stockCode, int price, int count) override {
		kiwer_api.sell(stockCode, count, price);
	}

	int getPrice(const string& stockCode) override {
		return kiwer_api.currentPrice(stockCode);
	}
};