include_guard(GLOBAL)

find_program(WINDEPLOYQT NAMES windeployqt HINTS "${QTDIR}" ENV QTDIR PATH_SUFFIXES bin)

if(NOT WINDEPLOYQT)
    message(WARNING "Cannot find windeployqt")
endif()

function(deployqt)
    cmake_parse_arguments(CWD "" "TARGET;OUTDIR" "" ${ARGN})
    if(NOT CWD_TARGET)
        message(FATAL_ERROR "No target specified")
    endif()
    if(NOT DEPLOYQT_OUTPUT_DIRECTORY)
        set(DEPLOYQT_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/qt")
    endif()
    if(CWD_OUTDIR)
        set(CWD_OUTDIR "${CWD_OUTDIR}")
    else()
        set(CWD_OUTDIR "${DEPLOYQT_OUTPUT_DIRECTORY}")
    endif()

    set(OUTDIRPARAM "--dir \"${CWD_OUTDIR}\"")
    add_custom_command(TARGET ${CWD_TARGET} PRE_LINK
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${CWD_OUTDIR}/$<CONFIG>"
        ${WINDEPLOYQT} "$<TARGET_FILE:${CWD_TARGET}>" ${OUTDIRPARAM}
    )
endfunction()
