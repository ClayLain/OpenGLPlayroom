#include <gtest/gtest.h>

#include <shader_package/PackageLoader.h>

namespace shaders_test
{

TEST(PackageLoader, Unzip)
{
    auto loader = shaders::PackageLoader {};
    const auto result = loader.load("test_data/test_package.shp");

    if (!result.has_value()) {
        FAIL() << result.error().description();
    }

    EXPECT_EQ(result->id(), shaders::PackageId::from_string("{026aac03-89c4-4eed-ba77-ea523e1dad4a}"));
    EXPECT_EQ(result->version(), semver::from_string_noexcept("0.1.2"));

    const auto shaders = result->shaders();
    EXPECT_EQ(shaders.size(), 2);

    std::set<shaders::Type> foundShaderTypes;
    for (const auto &shaderInfo : shaders) {
        if (shaderInfo.content.empty()) {
            FAIL() << "Empty shader data";
        }
    }
}

}
