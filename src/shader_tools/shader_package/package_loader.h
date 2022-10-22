#pragma once

#include <string>

#include <error_handling/error.h>
#include <quazip/quazip.h>
#include <tl/expected.hpp>

#include "package.h"

namespace shaders
{

class PackageLoader
{
public:
    tl::expected<Package, error_handling::Error> load(const std::string &path);

private:
    tl::expected<QString, error_handling::Error> readFileContent(const QString &path);
    tl::expected<ShaderInfo, error_handling::Error> parseShaderInfo(const QJsonObject &object);
    tl::expected<Package, error_handling::Error> parseManifest(const QString &manifestContent);

    QuaZip m_archive;
};

}
