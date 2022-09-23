function(cleanup_includedir INCLUDEDIR HEADERS)
    file(GLOB_RECURSE old_headers LIST_DIRECTORIES false "${INCLUDEDIR}/*")
    list(SORT HEADERS)
    list(SORT old_headers)
    foreach(hdr IN LISTS old_headers)
        list(FIND HEADERS "${hdr}" index)
        if(index EQUAL -1)
            file(REMOVE "${hdr}")
        endif()
    endforeach()
endfunction()

function(create_includedir)
    cmake_parse_arguments(CID "" "TARGET;DIR" "HEADERS" ${ARGN})

    set(includeroot "${CMAKE_CURRENT_BINARY_DIR}/include")
    set(includedir "${CMAKE_CURRENT_BINARY_DIR}/include/${CID_DIR}")

    if(NOT EXISTS "${includedir}")
        file(MAKE_DIRECTORY "${includedir}")
    endif()

    set(result_headers)
    foreach(header IN LISTS CID_HEADERS)
        get_filename_component(result_header "${header}" NAME)
        set(result_header_path "${includedir}/${header}")
        list(APPEND result_headers "${result_header_path}")

        if(NOT IS_ABSOLUTE "${header}")
                set(header "${CMAKE_CURRENT_SOURCE_DIR}/${header}")
        endif()

        file(GENERATE OUTPUT "${result_header_path}" CONTENT "#include \"${header}\"")
    endforeach()

    cleanup_includedir("${includedir}" "${result_headers}")

    target_include_directories(${CID_TARGET} INTERFACE "${includeroot}")

    add_library(${CID_TARGET}_headers INTERFACE ${CID_HEADERS})
    target_include_directories(${CID_TARGET}_headers INTERFACE)
    source_group("Header Files 2" FILES ${PRE_HEADERS})
endfunction()
