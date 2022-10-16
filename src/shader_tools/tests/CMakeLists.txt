set(test_source
    PackageLoader_test.cpp
)

set(fragment_shaders
    test_data/default.frag
    test_data/default2.frag
)

set(vertex_shaders
    test_data/default.vert
    test_data/default2.vert
)


add_executable(shader_tools_test ${test_source})
target_link_libraries(shader_tools_test
    PUBLIC
    GTest::gtest_main
    shader_package
)
add_dependencies(shader_package test_package)

compile_shader_package(
    PACKAGE test_package
    ID "{7b9ea976-a61f-4ae6-9679-3f8460149419}"
    VERSION "1.2.3"
    VERTEX_SHADERS "${vertex_shaders}"
    FRAGMENT_SHADERS "${fragment_shaders}"
)

gtest_discover_tests(shader_tools_test DISCOVERY_MODE PRE_TEST)
