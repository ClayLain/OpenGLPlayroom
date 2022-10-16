#include <gtest/gtest.h>

#include <shader_package/PackageLoader.h>

namespace shaders_test
{

TEST(PackageLoader, Unzip)
{
    auto loader = shaders::PackageLoader {};
    const auto result = loader.load("test_package.shp");

    if (!result.has_value()) {
        FAIL() << result.error().description();
    }

    EXPECT_EQ(result->id(), shaders::PackageId::from_string("{7b9ea976-a61f-4ae6-9679-3f8460149419}"));
    EXPECT_EQ(result->version(), semver::from_string_noexcept("1.2.3"));

    const auto shaders = result->shaders();
    EXPECT_EQ(shaders.size(), 4);

    std::set<shaders::Type> foundShaderTypes;
    for (const auto &shaderInfo : shaders) {
        if (shaderInfo.content.empty()) {
            FAIL() << "Empty shader data";
        }
    }
}

}
