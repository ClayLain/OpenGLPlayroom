add_subdirectory(res)

set(source
    debug.cpp
    debug.h
    main.cpp
    shaders.cpp
    shaders.h
)

add_executable(opengl_playroom ${source})

add_dependencies(opengl_playroom shaders)
target_link_libraries(opengl_playroom
    PRIVATE expected
    PRIVATE GLFWPP

    PRIVATE globjects::globjects
    PRIVATE glbinding::glbinding
    PRIVATE glbinding::glbinding-aux
)

target_compile_definitions(opengl_playroom PRIVATE GLFW_INCLUDE_NONE)
