#pragma once
#include <string>

#include <gmock/gmock.h>

#include "ILogger.h"

class MockLogger : public ILogger {
public:
	MOCK_METHOD(void, log, (const std::string& message), (override));
};
