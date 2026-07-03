#include "gmock/gmock.h"
using namespace testing;

#include "../driver/KiwerStockDriver.h"

class KiwerDriverTest : public ::testing::Test {
protected:
	KiwerStockDriver kiwer_driver;
};

TEST_F(KiwerDriverTest, LoginSuccessMessage) {
	internal::CaptureStdout();
	kiwer_driver.login("hong", "1234");
	string output = internal::GetCapturedStdout();

	EXPECT_THAT(output, HasSubstr("hong"));
	EXPECT_THAT(output, HasSubstr("login success"));
}

TEST_F(KiwerDriverTest, BuyPrintsBuyMessageWithPriceAndCount) {
	internal::CaptureStdout();
	kiwer_driver.buy("005930", 70000, 10);
	std::string output = internal::GetCapturedStdout();

	EXPECT_THAT(output, HasSubstr("005930"));
	EXPECT_THAT(output, HasSubstr("Buy stock"));
	EXPECT_THAT(output, StrEq("005930 : Buy stock ( 70000 * 10)\n"));
}

TEST_F(KiwerDriverTest, SellPrintsSellMessageWithPriceAndCount) {
	internal::CaptureStdout();
	kiwer_driver.sell("005930", 70000, 10);
	string output = internal::GetCapturedStdout();

	EXPECT_THAT(output, HasSubstr("70000"));
	EXPECT_THAT(output, HasSubstr("10"));
	EXPECT_THAT(output, StrEq("005930 : Sell stock ( 70000 * 10)\n"));
}

TEST_F(KiwerDriverTest, CurrentPriceReturnsValueInExpectedRange) {
	int price = kiwer_driver.getPrice("005930");

	EXPECT_GE(price, 5000);
	EXPECT_LE(price, 5900);
}
