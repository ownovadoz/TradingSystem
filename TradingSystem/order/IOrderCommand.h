#pragma once
#include <string>

class IOrderCommand {
public:
	virtual ~IOrderCommand() = default;

	virtual void execute() = 0;
	virtual std::string description() const = 0;
};
