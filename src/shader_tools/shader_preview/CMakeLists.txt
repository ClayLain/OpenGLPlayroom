set(source
    application_strings.cpp
    application_strings.h
    argument_parser.cpp
    argument_parser.h
    shader_preview_ui.cpp
    shader_preview_ui.h
    main.cpp
)

add_executable(shader_preview ${source})
target_link_libraries(shader_preview
    PRIVATE GLFWPP
    PRIVATE cxxopts
    PRIVATE error_handling
    PRIVATE expected
    PRIVATE file_utils
    PRIVATE globjects::globjects
    PRIVATE glbinding::glbinding
    PRIVATE glbinding::glbinding-aux
)

target_compile_definitions(shader_preview PRIVATE GLFW_INCLUDE_NONE)
deploy_glbinding(TARGET shader_preview)
deploy_globjects(TARGET shader_preview)
