set(shader_source
    shaders/default.frag
    shaders/default.vert
)

add_custom_target(shaders
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        "${CMAKE_CURRENT_BINARY_DIR}/shaders"
    SOURCES ${shader_source}
)
