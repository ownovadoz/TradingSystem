#include <gmock/gmock.h>
#include "auto_trading_system.h"
#include <memory>

class AutoTradingSystemTest : public ::testing::Test {
protected:
	void SetUp() override {
	}

	void login() {
	}
};

TEST_F(AutoTradingSystemTest, isAuthorizedFail) {

}

TEST_F(AutoTradingSystemTest, isAuthorizedSuccess) {
}

TEST_F(AutoTradingSystemTest, buyBeforeLogin) {
}

TEST_F(AutoTradingSystemTest, sellBeforeLogin) {
}

TEST_F(AutoTradingSystemTest, buyNiceTimingBeforeLogin) {
}

TEST_F(AutoTradingSystemTest, sellNiceTimingBeforeLogin) {
}

TEST_F(AutoTradingSystemTest, buyAfterLogin) {
}

TEST_F(AutoTradingSystemTest, sellAfterLogin) {
}

TEST_F(AutoTradingSystemTest, getPrice) {
}

TEST_F(AutoTradingSystemTest, butNiceTimingAfterLogin) {
}

TEST_F(AutoTradingSystemTest, sellNiceTimingAfterLogin) {
}
