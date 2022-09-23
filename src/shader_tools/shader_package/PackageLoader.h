#pragma once

#include <string>

#include <tl/expected.hpp>

#include "Package.h"
#include "Error.h"

namespace shaders
{

class PackageLoader
{
public:
    static tl::expected<Package, Error> load(const std::string &path);
};

}
