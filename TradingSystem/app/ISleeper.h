#pragma once
#include <chrono>

class ISleeper {
public:
	virtual ~ISleeper() = default;

	virtual void sleep(std::chrono::milliseconds duration) = 0;
};
