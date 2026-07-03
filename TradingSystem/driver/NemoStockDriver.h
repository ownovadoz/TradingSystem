#pragma once
#include "IStockBrockerDriver.h"
#include "../api/nemo_api.cpp"

using std::string;

class NemoStockBrockerDriver : public IStockBrockerDriver {
private:
    NemoAPI nemoApi;
public:
    void login(const string& id, const string& password) override {
        nemoApi.certification(id, password);
    }
    void buy(const string& stockCode, int price, int count) override {
        nemoApi.purchasingStock(stockCode, price, count);
    }
    void sell(const string& stockCode, int price, int count) override {
        nemoApi.sellingStock(stockCode, price, count);
    }
    int getPrice(const string& stockCode) override {
        return nemoApi.getMarketPrice(stockCode, 1);
    }
};
