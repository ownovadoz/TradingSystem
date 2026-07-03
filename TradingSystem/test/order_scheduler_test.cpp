#include <chrono>
#include <memory>

#include <gmock/gmock.h>

#include "order/OrderScheduler.h"
#include "order/MockOrderCommand.h"
#include "MockLogger.h"

using ::testing::_;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

std::chrono::system_clock::time_point timeFromNow(int seconds) {
	return std::chrono::system_clock::now() + std::chrono::seconds(seconds);
}

}

class OrderSchedulerTest : public ::testing::Test {
protected:
	std::unique_ptr<NiceMock<MockLogger>> loggerOwned = std::make_unique<NiceMock<MockLogger>>();
	NiceMock<MockLogger>* logger = loggerOwned.get();
	OrderScheduler scheduler{ std::move(loggerOwned) };
};

TEST_F(OrderSchedulerTest, scheduleOrderAddsToQueueWithoutExecuting) {
	auto command = std::make_unique<NiceMock<MockOrderCommand>>();
	EXPECT_CALL(*command, execute()).Times(0);

	scheduler.scheduleOrder(std::move(command), timeFromNow(60));

	EXPECT_EQ(1u, scheduler.pendingOrderCount());
}

TEST_F(OrderSchedulerTest, runDueOrdersExecutesOrdersWhoseTimeHasArrived) {
	auto command = std::make_unique<NiceMock<MockOrderCommand>>();
	EXPECT_CALL(*command, execute()).Times(1);

	scheduler.scheduleOrder(std::move(command), timeFromNow(-1));
	scheduler.runDueOrders(std::chrono::system_clock::now());

	EXPECT_EQ(0u, scheduler.pendingOrderCount());
}

TEST_F(OrderSchedulerTest, runDueOrdersDoesNotExecuteFutureOrders) {
	auto command = std::make_unique<NiceMock<MockOrderCommand>>();
	EXPECT_CALL(*command, execute()).Times(0);

	scheduler.scheduleOrder(std::move(command), timeFromNow(3600));
	scheduler.runDueOrders(std::chrono::system_clock::now());

	EXPECT_EQ(1u, scheduler.pendingOrderCount());
}

TEST_F(OrderSchedulerTest, runDueOrdersLogsBeforeAndAfterExecution) {
	auto command = std::make_unique<NiceMock<MockOrderCommand>>();
	ON_CALL(*command, description()).WillByDefault(Return("BUY 005930 x10 @70000"));

	{
		InSequence sequence;
		EXPECT_CALL(*logger, log(_)).Times(1);
		EXPECT_CALL(*command, execute()).Times(1);
		EXPECT_CALL(*logger, log(_)).Times(1);
	}

	scheduler.scheduleOrder(std::move(command), timeFromNow(-1));
	scheduler.runDueOrders(std::chrono::system_clock::now());
}
