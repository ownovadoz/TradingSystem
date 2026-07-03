#include "gmock/gmock.h"
#include "../driver/NemoStockDriver.h"

using namespace testing;

class NemoDriverTest : public Test {
protected:
    NemoStockBrockerDriver driver;
};

TEST_F(NemoDriverTest, LoginPrintsLoginGoodMessage) {
    internal::CaptureStdout();
    driver.login("hong", "1234");
    std::string output = internal::GetCapturedStdout();
    EXPECT_THAT(output, HasSubstr("hong"));
    EXPECT_THAT(output, HasSubstr("login GOOD"));
    EXPECT_THAT(output, StrEq("[NEMO]hong login GOOD\n"));
}

TEST_F(NemoDriverTest, LoginPrintsCorrectIdInMessage) {
    internal::CaptureStdout();
    driver.login("kim", "pass");
    std::string output = internal::GetCapturedStdout();
    EXPECT_THAT(output, StrEq("[NEMO]kim login GOOD\n"));
}

TEST_F(NemoDriverTest, BuyPrintsBuyMessageWithPriceAndCount) {
    internal::CaptureStdout();
    driver.buy("005930", 70000, 10);
    std::string output = internal::GetCapturedStdout();
    EXPECT_THAT(output, HasSubstr("005930"));
    EXPECT_THAT(output, HasSubstr("buy stock"));
    EXPECT_THAT(output, StrEq("[NEMO]005930 buy stock ( price : 70000 ) * ( count : 10)\n"));
}

TEST_F(NemoDriverTest, BuyPriceAndCountAreNotSwapped) {
    internal::CaptureStdout();
    driver.buy("005930", 50000, 3);
    std::string output = internal::GetCapturedStdout();
    EXPECT_THAT(output, StrEq("[NEMO]005930 buy stock ( price : 50000 ) * ( count : 3)\n"));
}

TEST_F(NemoDriverTest, SellPrintsSellMessageWithPriceAndCount) {
    internal::CaptureStdout();
    driver.sell("005930", 70000, 10);
    std::string output = internal::GetCapturedStdout();
    EXPECT_THAT(output, HasSubstr("005930"));
    EXPECT_THAT(output, HasSubstr("sell stock"));
    EXPECT_THAT(output, StrEq("[NEMO]005930 sell stock ( price : 70000 ) * ( count : 10)\n"));
}

TEST_F(NemoDriverTest, SellPriceAndCountAreNotSwapped) {
    internal::CaptureStdout();
    driver.sell("005930", 50000, 3);
    std::string output = internal::GetCapturedStdout();
    EXPECT_THAT(output, StrEq("[NEMO]005930 sell stock ( price : 50000 ) * ( count : 3)\n"));
}

TEST_F(NemoDriverTest, GetPriceReturnsValueInExpectedRange) {
    int price = driver.getPrice("005930");
    EXPECT_GE(price, 5000);
    EXPECT_LE(price, 5900);
}

TEST_F(NemoDriverTest, GetPriceWithDifferentStockCode) {
    int price = driver.getPrice("000660");
    EXPECT_GE(price, 5000);
    EXPECT_LE(price, 5900);
}
