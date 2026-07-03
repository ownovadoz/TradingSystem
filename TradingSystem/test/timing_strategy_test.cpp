#include <vector>

#include <gmock/gmock.h>

#include "strategy/RisingTrendStrategy.h"
#include "strategy/MovingAverageStrategy.h"
#include "strategy/BreakoutStrategy.h"

TEST(RisingTrendStrategyTest, shouldBuyWhenThreeConsecutiveRises) {
	RisingTrendStrategy strategy;
	EXPECT_TRUE(strategy.shouldBuy({ 100, 110, 120 }));
}

TEST(RisingTrendStrategyTest, shouldNotBuyWhenNotConsecutiveRises) {
	RisingTrendStrategy strategy;
	EXPECT_FALSE(strategy.shouldBuy({ 100, 90, 120 }));
}

TEST(RisingTrendStrategyTest, shouldSellWhenThreeConsecutiveFalls) {
	RisingTrendStrategy strategy;
	EXPECT_TRUE(strategy.shouldSell({ 120, 110, 100 }));
}

TEST(RisingTrendStrategyTest, shouldNotSellWhenNotConsecutiveFalls) {
	RisingTrendStrategy strategy;
	EXPECT_FALSE(strategy.shouldSell({ 100, 110, 100 }));
}

TEST(MovingAverageStrategyTest, shouldBuyWhenPriceBreaksAboveAverage) {
	MovingAverageStrategy strategy(3);
	EXPECT_TRUE(strategy.shouldBuy({ 100, 100, 100, 130 }));
}

TEST(MovingAverageStrategyTest, shouldNotBuyWhenPriceBelowAverage) {
	MovingAverageStrategy strategy(3);
	EXPECT_FALSE(strategy.shouldBuy({ 100, 100, 100, 90 }));
}

TEST(MovingAverageStrategyTest, shouldSellWhenPriceBreaksBelowAverage) {
	MovingAverageStrategy strategy(3);
	EXPECT_TRUE(strategy.shouldSell({ 100, 100, 100, 70 }));
}

TEST(MovingAverageStrategyTest, shouldNotSellWhenPriceAboveAverage) {
	MovingAverageStrategy strategy(3);
	EXPECT_FALSE(strategy.shouldSell({ 100, 100, 100, 130 }));
}

TEST(BreakoutStrategyTest, shouldBuyWhenPriceBreaksAboveRecentHigh) {
	BreakoutStrategy strategy(3);
	EXPECT_TRUE(strategy.shouldBuy({ 100, 105, 103, 110 }));
}

TEST(BreakoutStrategyTest, shouldNotBuyWhenPriceWithinRecentRange) {
	BreakoutStrategy strategy(3);
	EXPECT_FALSE(strategy.shouldBuy({ 100, 105, 103, 104 }));
}

TEST(BreakoutStrategyTest, shouldSellWhenPriceBreaksBelowRecentLow) {
	BreakoutStrategy strategy(3);
	EXPECT_TRUE(strategy.shouldSell({ 100, 95, 98, 90 }));
}

TEST(BreakoutStrategyTest, shouldNotSellWhenPriceWithinRecentRange) {
	BreakoutStrategy strategy(3);
	EXPECT_FALSE(strategy.shouldSell({ 100, 95, 98, 96 }));
}
