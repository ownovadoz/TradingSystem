#include "auto_trading_system.h"
#include "mock_stock_broker_driver.h"
#include "mock_stock_driver_factory.h"
#include <gmock/gmock.h>
#include <memory>

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ByMove;
using ::testing::_;

TEST(AutoTradingSystemNoBrokerTest, didNotSelectStockBroker) {
	AutoTradingSystem system;
	EXPECT_THROW(system.login("id", "pass"), BrokerNotSelectedException);
}

TEST(AutoTradingSystemFactoryTest, BrokerType으로_선택하면_Factory가_생성한_Driver를_사용한다) {
	auto factory = std::make_unique<MockStockDriverFactory>();
	auto driverOwned = std::make_unique<NiceMock<MockStockDriver>>();
	NiceMock<MockStockDriver>* driverRaw = driverOwned.get();

	EXPECT_CALL(*factory, create(BrokerType::Kiwer))
		.WillOnce(Return(ByMove(std::move(driverOwned))));

	AutoTradingSystem system{ std::move(factory) };
	system.selectStockBroker(BrokerType::Kiwer);

	EXPECT_CALL(*driverRaw, login("mincoding", "1234")).Times(1);
	system.login("mincoding", "1234");
}

class AutoTradingSystemTest : public ::testing::Test {
protected:
	AutoTradingSystem system;
	NiceMock<MockStockDriver>* mockDriver = nullptr;

	void SetUp() override {
		auto driver = std::make_unique<NiceMock<MockStockDriver>>();
		mockDriver = driver.get();
		system.selectStockBroker(std::move(driver));
	}

	void login() {
		system.login("mincoding", "1234");
	}
};

TEST_F(AutoTradingSystemTest, isAuthorizedFail) {
	EXPECT_FALSE(system.isAuthorized());
}

TEST_F(AutoTradingSystemTest, isAuthorizedSuccess) {
	EXPECT_CALL(*mockDriver, login("mincoding", "1234")).Times(1);

	login();

	EXPECT_TRUE(system.isAuthorized());
}

TEST_F(AutoTradingSystemTest, buyBeforeLogin) {
	EXPECT_CALL(*mockDriver, buy(_, _, _)).Times(0);

	EXPECT_THROW(system.buy("005930", 70000, 10), NotAuthorizedException);
}

TEST_F(AutoTradingSystemTest, sellBeforeLogin) {
	EXPECT_CALL(*mockDriver, sell(_, _, _)).Times(0);

	EXPECT_THROW(system.sell("005930", 71000, 5), NotAuthorizedException);
}

TEST_F(AutoTradingSystemTest, buyNiceTimingBeforeLogin) {
	EXPECT_CALL(*mockDriver, getPrice(_)).Times(0);
	EXPECT_CALL(*mockDriver, buy(_, _, _)).Times(0);

	EXPECT_THROW(system.buyNiceTiming("005930", 10000), NotAuthorizedException);
}

TEST_F(AutoTradingSystemTest, sellNiceTimingBeforeLogin) {
	EXPECT_CALL(*mockDriver, getPrice(_)).Times(0);
	EXPECT_CALL(*mockDriver, sell(_, _, _)).Times(0);

	EXPECT_THROW(system.sellNiceTiming("005930", 10), NotAuthorizedException);
}

TEST_F(AutoTradingSystemTest, buyAfterLogin) {
	login();
	EXPECT_CALL(*mockDriver, buy("005930", 70000, 10)).Times(1);

	system.buy("005930", 70000, 10);
}

TEST_F(AutoTradingSystemTest, sellAfterLogin) {
	login();
	EXPECT_CALL(*mockDriver, sell("005930", 71000, 5)).Times(1);

	system.sell("005930", 71000, 5);
}

TEST_F(AutoTradingSystemTest, getPrice) {
	EXPECT_CALL(*mockDriver, getPrice("005930")).WillOnce(Return(12345));

	EXPECT_EQ(12345, system.getPrice("005930"));
}

TEST_F(AutoTradingSystemTest, butNiceTimingAfterLogin) {
}

TEST_F(AutoTradingSystemTest, sellNiceTimingAfterLogin) {
}
