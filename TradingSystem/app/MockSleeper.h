#pragma once
#include <chrono>

#include <gmock/gmock.h>

#include "ISleeper.h"

class MockSleeper : public ISleeper {
public:
	MOCK_METHOD(void, sleep, (std::chrono::milliseconds duration), (override));
};
