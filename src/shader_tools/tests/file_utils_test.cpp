#include <gtest/gtest.h>

#include <file_utils/file_utils.h>

namespace shaders_test
{

TEST(FileUtils, ReadInvalid)
{
    const auto result = file_utils::readTextFileContent("INVALID_PATH");
    if(result.has_value()) {
        FAIL() << "Read operation must fail with an invalid path";
    }
}

TEST(FileUtils, Read)
{
    const auto result = file_utils::readTextFileContent("test_file.txt");
    if (!result.has_value()) {
        FAIL() << result.error().description();
    }

    const auto resultString = result.value();
    EXPECT_EQ(resultString, "test file data");
}

}
