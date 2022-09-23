#pragma once

#include <string>
#include <glbinding/gl/gl.h>

namespace playroom::shaders
{

enum class ShaderType
{
    Vertex,
    Fragment
};

std::string readShaderFile(const std::string &path);

gl::GLuint createShader(const std::string &vertexShader, const std::string &fragmentShader);

}
