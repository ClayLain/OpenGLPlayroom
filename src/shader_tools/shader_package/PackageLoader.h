#pragma once

#include <string>

#include <tl/expected.hpp>
#include <quazip/quazip.h>

#include "Package.h"
#include "Error.h"

namespace shaders
{

class PackageLoader
{
public:
    tl::expected<Package, Error> load(const std::string &path);

private:
    tl::expected<QString, Error> readFileContent(const QString &path);
    tl::expected<ShaderInfo, Error> parseShaderInfo(const QJsonObject &object);
    tl::expected<Package, Error> parseManifest(const QString &manifestContent);

    QuaZip m_archive;
};

}
