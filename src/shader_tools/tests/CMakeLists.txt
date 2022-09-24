set(test_source
    PackageLoader_test.cpp
)

add_executable(shader_package_test ${test_source})
target_link_libraries(shader_package_test
    PUBLIC
    GTest::gtest_main
    shader_package
)

file(COPY "${CMAKE_CURRENT_LIST_DIR}/test_data" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

gtest_discover_tests(shader_package_test DISCOVERY_MODE PRE_TEST)
