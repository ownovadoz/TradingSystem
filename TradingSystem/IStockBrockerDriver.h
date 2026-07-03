#define interface struct
#include <string>
using std::string;
interface IStockBrockerDriver{
public:
    virtual ~IStockBrockerDriver() {}

    virtual void login(const string & id, const string & password) = 0;
    virtual void buy(const string& stockCode, int price, int count) = 0;
    virtual void sell(const string& stockCode, int price, int count) = 0;
    virtual int getPrice(const string& stockCode) = 0;
};