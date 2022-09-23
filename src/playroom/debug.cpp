#include "debug.h"

#include <iostream>

#include <glbinding/gl/gl.h>

namespace playroom::debug
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

void callback(
        gl::GLenum source,
        gl::GLenum type,
        gl::GLuint id,
        gl::GLenum severity,
        gl::GLsizei length,
        const gl::GLchar *message,
        const void* userParam
        )
{
    log(message);
}

}

namespace playroom::debug
{

void enableOpenGLLogs()
{
    glEnable(gl::GL_DEBUG_OUTPUT);
    glDebugMessageCallback(callback, nullptr);
}

void log(const std::string &message, Level level)
{
    std::cout << logLevelPrefix(level) + message << std::endl;
}

}
