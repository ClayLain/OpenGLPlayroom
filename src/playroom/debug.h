#pragma once

#include <string>

namespace playroom::debug
{

enum class Level
{
    Info,
    Warning,
    Error
};

void enableOpenGLLogs();
void log(const std::string &message, Level level = Level::Info);

}
