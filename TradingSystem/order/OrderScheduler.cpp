#include "OrderScheduler.h"
#include "../ConsoleLogger.h"

OrderScheduler::OrderScheduler(std::unique_ptr<ILogger> logger)
	: logger(logger ? std::move(logger) : std::make_unique<ConsoleLogger>()) {
}

void OrderScheduler::scheduleOrder(std::unique_ptr<IOrderCommand> command, std::chrono::system_clock::time_point execution_time) {
	scheduled_orders.push_back(ScheduledOrder{ std::move(command), execution_time });
}

void OrderScheduler::runDueOrders(std::chrono::system_clock::time_point current_time) {
	std::vector<ScheduledOrder> remaining_orders;

	for (auto& order : scheduled_orders) {
		if (order.execution_time > current_time) {
			remaining_orders.push_back(std::move(order));
			continue;
		}

		logger->log("Executing order: " + order.command->description());
		order.command->execute();
		logger->log("Executed order: " + order.command->description());
	}

	scheduled_orders = std::move(remaining_orders);
}

size_t OrderScheduler::pendingOrderCount() const {
	return scheduled_orders.size();
}
