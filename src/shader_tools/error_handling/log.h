#pragma once

#include <string>

namespace error_handling
{

enum class Level
{
    Info,
    Warning,
    Error
};

void log(const std::string &message, Level level = Level::Info);

}
