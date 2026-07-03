#include <gmock/gmock.h>
#include <memory>

#include "AutoTradingSystem.h"
#include "mock_stock_broker_driver.h"
#include "mock_stock_driver_factory.h"
#include "strategy/MockTimingStrategy.h"

using ::testing::NiceMock;
using ::testing::Return;
using ::testing::ByMove;
using ::testing::_;

TEST(AutoTradingSystemNoBrokerTest, didNotSelectStockBroker) {
	AutoTradingSystem system;
	EXPECT_THROW(system.login("id", "pass"), BrokerNotSelectedException);
}

TEST(AutoTradingSystemFactoryTest, factoryChooseBrokerByType) {
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

TEST_F(AutoTradingSystemTest, buyNiceTimingWithDefaultStrategyBuysOnRisingTrend) {
	login();
	EXPECT_CALL(*mockDriver, getPrice("005930"))
		.WillOnce(Return(100))
		.WillOnce(Return(110))
		.WillOnce(Return(120));
	EXPECT_CALL(*mockDriver, buy("005930", 120, _)).Times(1);

	system.buyNiceTiming("005930", 1200);
}

TEST_F(AutoTradingSystemTest, buyNiceTimingUsesInjectedStrategyToDecideBuy) {
	auto strategyOwned = std::make_unique<NiceMock<MockTimingStrategy>>();
	NiceMock<MockTimingStrategy>* strategy = strategyOwned.get();
	system.setTimingStrategy(std::move(strategyOwned));

	login();
	EXPECT_CALL(*mockDriver, getPrice("005930")).WillRepeatedly(Return(70000));
	EXPECT_CALL(*strategy, shouldBuy(_)).WillOnce(Return(true));
	EXPECT_CALL(*mockDriver, buy("005930", 70000, _)).Times(1);

	system.buyNiceTiming("005930", 700000);
}

TEST_F(AutoTradingSystemTest, buyNiceTimingDoesNotBuyWhenStrategySaysNo) {
	auto strategyOwned = std::make_unique<NiceMock<MockTimingStrategy>>();
	NiceMock<MockTimingStrategy>* strategy = strategyOwned.get();
	system.setTimingStrategy(std::move(strategyOwned));

	login();
	EXPECT_CALL(*mockDriver, getPrice("005930")).WillRepeatedly(Return(70000));
	EXPECT_CALL(*strategy, shouldBuy(_)).WillOnce(Return(false));
	EXPECT_CALL(*mockDriver, buy(_, _, _)).Times(0);

	system.buyNiceTiming("005930", 700000);
}

TEST_F(AutoTradingSystemTest, sellNiceTimingUsesInjectedStrategyToDecideSell) {
	auto strategyOwned = std::make_unique<NiceMock<MockTimingStrategy>>();
	NiceMock<MockTimingStrategy>* strategy = strategyOwned.get();
	system.setTimingStrategy(std::move(strategyOwned));

	login();
	EXPECT_CALL(*mockDriver, getPrice("005930")).WillRepeatedly(Return(70000));
	EXPECT_CALL(*strategy, shouldSell(_)).WillOnce(Return(true));
	EXPECT_CALL(*mockDriver, sell("005930", 70000, 5)).Times(1);

	system.sellNiceTiming("005930", 5);
}

TEST_F(AutoTradingSystemTest, sellNiceTimingDoesNotSellWhenStrategySaysNo) {
	auto strategyOwned = std::make_unique<NiceMock<MockTimingStrategy>>();
	NiceMock<MockTimingStrategy>* strategy = strategyOwned.get();
	system.setTimingStrategy(std::move(strategyOwned));

	login();
	EXPECT_CALL(*mockDriver, getPrice("005930")).WillRepeatedly(Return(70000));
	EXPECT_CALL(*strategy, shouldSell(_)).WillOnce(Return(false));
	EXPECT_CALL(*mockDriver, sell(_, _, _)).Times(0);

	system.sellNiceTiming("005930", 5);
}