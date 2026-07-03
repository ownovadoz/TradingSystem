#pragma once
#include <chrono>
#include <cstddef>
#include <memory>
#include <vector>

#include "IOrderCommand.h"
#include "../ILogger.h"

class OrderScheduler {
public:
	explicit OrderScheduler(std::unique_ptr<ILogger> logger = nullptr);

	void scheduleOrder(std::unique_ptr<IOrderCommand> command, std::chrono::system_clock::time_point execution_time);
	void runDueOrders(std::chrono::system_clock::time_point current_time);
	size_t pendingOrderCount() const;

private:
	struct ScheduledOrder {
		std::unique_ptr<IOrderCommand> command;
		std::chrono::system_clock::time_point execution_time;
	};

	std::unique_ptr<ILogger> logger;
	std::vector<ScheduledOrder> scheduled_orders;
};
