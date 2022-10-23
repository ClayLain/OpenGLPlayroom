#include "shader_preview_ui.h"

#include <error_handling/error_handling_utils.h>
#include <file_utils/file_utils.h>
#include <glfwpp/glfwpp.h>

#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>

#include "argument_parser.h"
#include "application_strings.h"

namespace shader_preview
{

std::string defaultVertexShaderCode()
{
    static const auto code = R"D(
        #version 330 core
        const vec2 quadVertices[4] = vec2[4](
            vec2( -1.0, -1.0),
            vec2( 1.0, -1.0),
            vec2( -1.0, 1.0),
            vec2( 1.0, 1.0)
        );
        void main()
        {
            gl_Position = vec4(quadVertices[gl_VertexID], 0.0, 1.0);
        }
    )D";

    return code;
}

gl::GLuint compileShader(gl::GLenum type, const std::string &source)
{
    const auto id = gl::glCreateShader(type);
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
        gl::glDeleteShader(id);
        return 0;
    }

    return id;
}

gl::GLuint createShader(const std::string &fragmentShader)
{
    unsigned int program = gl::glCreateProgram();
    const auto vs = compileShader(gl::GL_VERTEX_SHADER, defaultVertexShaderCode());
    const auto fs = compileShader(gl::GL_FRAGMENT_SHADER, fragmentShader);

    gl::glAttachShader(program, vs);
    gl::glAttachShader(program, fs);
    gl::glLinkProgram(program);
    gl::glValidateProgram(program);

    gl::glDeleteShader(vs);
    gl::glDeleteShader(fs);

    return program;
}

void startPreviewUi(int argc, char *argv[])
{
    const auto options = argument_parser::parse(argc, argv)
            .or_else(error_handling::fatalError)
            .value();

    const auto glfwLibrary = glfw::init();
    auto window = glfw::Window { 640, 480, application_strings::g_applicationName.c_str() };
    glfw::makeContextCurrent(window);
    glbinding::initialize(glfwGetProcAddress);

    const auto fragmentShaderCode = file_utils::readTextFileContent(options.filePath)
            .or_else(error_handling::fatalError)
            .value();

    const auto shader = createShader(fragmentShaderCode);
    gl::glUseProgram(shader);

    while (!window.shouldClose()) {
        gl::glClear(gl::GL_COLOR_BUFFER_BIT);
        gl::glDrawArrays(gl::GL_TRIANGLE_STRIP, 0, 4);
        window.swapBuffers();
        glfw::pollEvents();
    }
}

}
