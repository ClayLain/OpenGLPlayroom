#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <glfwpp/glfwpp.h>

#include "debug.h"
#include "shaders.h"

using namespace playroom;

int main()
{
    const auto glfwLibrary = glfw::init();

    auto window = glfw::Window { 640, 480, "Hello World" };
    glfw::makeContextCurrent(window);
    glbinding::initialize(glfwGetProcAddress);

    debug::enableOpenGLLogs();

    float positions[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f, 0.5f
    };

    gl::GLuint buffer[] = {0};
    gl::glGenBuffers(1, buffer);
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, buffer[0]);
    gl::glBufferData(gl::GL_ARRAY_BUFFER, sizeof(float) * 6, positions, gl::GL_STATIC_DRAW);

    gl::glEnableVertexAttribArray(0);
    gl::glVertexAttribPointer(0, 2, gl::GL_FLOAT, gl::GL_FALSE, 2 * sizeof(float), 0);

    const auto vertexFile = shaders::readShaderFile(".\\shaders\\default.vert");
    const auto fragmentFile = shaders::readShaderFile(".\\shaders\\default.frag");
    const auto shader = playroom::shaders::createShader(vertexFile, fragmentFile);
    gl::glUseProgram(shader);
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);

    while (!window.shouldClose()) {
        gl::glClear(gl::GL_COLOR_BUFFER_BIT);
        gl::glDrawArrays(gl::GL_TRIANGLES, 0, 3);
        window.swapBuffers();
        glfw::pollEvents();
    }

    return 0;
}
