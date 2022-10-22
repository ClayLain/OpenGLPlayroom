#pragma once

#include <vector>
#include <string>

#include <include/uuid.h>
#include <semver.hpp>

namespace shaders
{

using PackageId = uuids::uuid;
using PackageVersion = semver::version;

enum class Type
{
    Vertex,
    Fragment
};

struct ShaderInfo
{
    Type type;
    std::string content;
};

class Package
{
public:
    explicit Package(
            const PackageId &id,
            const PackageVersion &version,
            const std::vector<ShaderInfo> &shaders
            );

    PackageId id() const;
    PackageVersion version() const;
    const std::vector<ShaderInfo> & shaders() const;

private:
    PackageId m_id;
    PackageVersion m_version;
    std::vector<ShaderInfo> m_shaders;
};

}
