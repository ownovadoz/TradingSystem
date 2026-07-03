#include <gmock/gmock.h>

#include "../order/BuyOrderCommand.h"
#include "../order/SellOrderCommand.h"
#include "../driver/mock_stock_broker_driver.h"

using ::testing::NiceMock;

TEST(BuyOrderCommandTest, executeCallsDriverBuy) {
	NiceMock<MockStockDriver> driver;
	EXPECT_CALL(driver, buy("005930", 70000, 10)).Times(1);

	BuyOrderCommand command(driver, "005930", 70000, 10);
	command.execute();
}

TEST(BuyOrderCommandTest, descriptionDescribesTheOrder) {
	NiceMock<MockStockDriver> driver;
	BuyOrderCommand command(driver, "005930", 70000, 10);

	EXPECT_EQ("BUY 005930 x10 @70000", command.description());
}

TEST(SellOrderCommandTest, executeCallsDriverSell) {
	NiceMock<MockStockDriver> driver;
	EXPECT_CALL(driver, sell("005930", 71000, 5)).Times(1);

	SellOrderCommand command(driver, "005930", 71000, 5);
	command.execute();
}

TEST(SellOrderCommandTest, descriptionDescribesTheOrder) {
	NiceMock<MockStockDriver> driver;
	SellOrderCommand command(driver, "005930", 71000, 5);

	EXPECT_EQ("SELL 005930 x5 @71000", command.description());
}
