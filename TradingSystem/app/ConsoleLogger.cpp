#include <iostream>

#include "ConsoleLogger.h"

void ConsoleLogger::log(const std::string& message) {
	std::cout << message << std::endl;
}
