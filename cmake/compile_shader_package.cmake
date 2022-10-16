include_guard(GLOBAL)

find_package(Python REQUIRED)

function(prepare_shader_path paths result)
    list(APPEND RESULT_ABS_PATHS_LIST "")
    foreach(F ${paths})
        if(NOT IS_ABSOLUTE ${F})
            set(F "${CMAKE_CURRENT_LIST_DIR}/${F}")
        endif()
        list(APPEND RESULT_ABS_PATHS_LIST ${F})
    endforeach()

    set(${result} "${RESULT_ABS_PATHS_LIST}" PARENT_SCOPE)
endfunction()

function(compile_shader_package)
    cmake_parse_arguments(OLGP "" "PACKAGE;ID;VERSION" "VERTEX_SHADERS;FRAGMENT_SHADERS" ${ARGN})

    set(SCRIPTS_DIR "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/../scripts")
    set(RESULT_FILE "${CMAKE_CURRENT_BINARY_DIR}/${OLGP_PACKAGE}.shp")
    set(FRAGMENT_SHADERS)
    set(VERTEX_SHADERS)

    prepare_shader_path("${OLGP_FRAGMENT_SHADERS}" FRAGMENT_SHADERS)
    prepare_shader_path("${OLGP_VERTEX_SHADERS}" VERTEX_SHADERS)

    add_custom_target(
        ${OLGP_PACKAGE} ALL
        COMMAND ${Python_EXECUTABLE} "${SCRIPTS_DIR}/compile_shader_package.py"
            "--id" "${OLGP_ID}"
            "--version" "${OLGP_VERSION}"
            "--destination" "${RESULT_FILE}"
            "--fshaders" ${FRAGMENT_SHADERS}
            "--vshaders" ${VERTEX_SHADERS}
        BYPRODUCTS "${RESULT_FILE}"
        COMMENT "Compile shader package ${OLGP_PACKAGE}"
        SOURCES ${OLGP_VERTEX_SHADERS} ${OLGP_FRAGMENT_SHADERS}
    )
endfunction()
