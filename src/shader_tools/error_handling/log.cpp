#include "log.h"

#include <iostream>

namespace error_handling
{

std::string logLevelPrefix(Level level)
{
    switch (level) {
    case Level::Info: return "Info: ";
    case Level::Warning: return "Warning: ";
    case Level::Error: return "Error: ";
    default: return "";
    }
}

void log(const std::string &message, Level level)
{
    std::cerr << logLevelPrefix(level) + message << std::endl;
}

}
