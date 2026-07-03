#pragma once
#include <string>

#include <gmock/gmock.h>

#include "IOrderCommand.h"

class MockOrderCommand : public IOrderCommand {
public:
	MOCK_METHOD(void, execute, (), (override));
	MOCK_METHOD(std::string, description, (), (const, override));
};
