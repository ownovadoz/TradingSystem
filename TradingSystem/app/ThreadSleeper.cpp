#include <thread>

#include "ThreadSleeper.h"

void ThreadSleeper::sleep(std::chrono::milliseconds duration) {
	std::this_thread::sleep_for(duration);
}
