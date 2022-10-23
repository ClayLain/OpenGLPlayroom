cmake_minimum_required(VERSION 3.23)

project(OGLPlayroom LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include("cmake/compile_shader_package.cmake")
include("cmake/deploy_qt.cmake")
include("cmake/deploy_gllibs.cmake")
include("cmake/include_dirs.cmake")
include(GoogleTest)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_PREFIX_PATH
    ${CMAKE_PREFIX_PATH}
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glbinding"
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glm"
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/globjects"
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/cpplocate"
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/glfwpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/zlib"
)

find_package(GLM REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Core)
find_package(glbinding REQUIRED)
find_package(globjects REQUIRED)

add_subdirectory(3rdparty/cxxopts)
add_subdirectory(3rdparty/expected)
add_subdirectory(3rdparty/glfwpp)
add_subdirectory(3rdparty/googletest)
add_subdirectory(3rdparty/quazip)
add_subdirectory(3rdparty/semver)
add_subdirectory(3rdparty/stduuid)

add_subdirectory(scripts)

enable_testing()
add_subdirectory(src)
