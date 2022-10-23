include_guard(GLOBAL)

function(deploy_glbinding)
    cmake_parse_arguments(OGLP "" "TARGET" "" ${ARGN})
    if(NOT OGLP_TARGET)
        message(FATAL_ERROR "No target specified")
    endif()

    get_property(glbinding_location TARGET glbinding::glbinding PROPERTY LOCATION)
    get_target_property(target_location ${OGLP_TARGET} BINARY_DIR)
    file(COPY ${glbinding_location} DESTINATION ${target_location})
endfunction()

function(deploy_globjects)
    cmake_parse_arguments(OGLP "" "TARGET" "" ${ARGN})
    if(NOT OGLP_TARGET)
        message(FATAL_ERROR "No target specified")
    endif()

    get_property(globjects_location TARGET globjects::globjects PROPERTY LOCATION)
    get_target_property(target_location ${OGLP_TARGET} BINARY_DIR)
    file(COPY ${globjects_location} DESTINATION ${target_location})
endfunction()
