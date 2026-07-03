#pragma once
#include <chrono>

#include "ISleeper.h"

class ThreadSleeper : public ISleeper {
public:
	void sleep(std::chrono::milliseconds duration) override;
};
