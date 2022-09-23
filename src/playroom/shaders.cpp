#include "shaders.h"

#include <fstream>
#include <iostream>
#include <optional>

#include <glbinding/gl/gl.h>

namespace playroom::shaders
{

std::optional<gl::GLenum> toGlEnumType(ShaderType type)
{
    switch (type) {
    case ShaderType::Fragment: return gl::GL_FRAGMENT_SHADER;
    case ShaderType::Vertex: return gl::GL_VERTEX_SHADER;
    default: return std::nullopt;
    }
}

gl::GLuint compileShader(ShaderType type, const std::string &source)
{
    const auto id = glCreateShader(toGlEnumType(type).value());
    const auto src = source.c_str();
    gl::glShaderSource(id, 1, &src, nullptr);
    gl::glCompileShader(id);

    int result;
    gl::glGetShaderiv(id, gl::GL_COMPILE_STATUS, &result);
    if (result == gl::GL_FALSE) {
        int length;
        gl::glGetShaderiv(id, gl::GL_INFO_LOG_LENGTH, &length);
        auto message = std::string(length, ' ');
        gl::glGetShaderInfoLog(id, length, &length, message.data());
        std::cout << "Failed to compile " << " shader: " << message << std::endl;
        gl::glDeleteShader(id);
        return 0;
    }

    return id;
}

}

namespace playroom::shaders
{

std::string readShaderFile(const std::string &path)
{
    auto stream = std::ifstream(path);
    if (!stream.is_open()) {
        return "";
    }
    return std::string(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
}

gl::GLuint createShader(const std::string &vertexShader, const std::string &fragmentShader)
{
    unsigned int program = gl::glCreateProgram();
    const auto vs = compileShader(ShaderType::Vertex, vertexShader);
    const auto fs = compileShader(ShaderType::Fragment, fragmentShader);

    gl::glAttachShader(program, vs);
    gl::glAttachShader(program, fs);
    gl::glLinkProgram(program);
    gl::glValidateProgram(program);

    gl::glDeleteShader(vs);
    gl::glDeleteShader(fs);

    return program;
}

}
