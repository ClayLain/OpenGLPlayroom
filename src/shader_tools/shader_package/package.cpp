#include "package.h"

namespace shaders
{

Package::Package(
        const PackageId &id,
        const PackageVersion &version,
        const std::vector<ShaderInfo> &shaders
        )
    : m_id { id }
    , m_version { version }
    , m_shaders { shaders }
{
}

PackageId Package::id() const
{
    return m_id;
}

PackageVersion Package::version() const
{
    return m_version;
}

const std::vector<ShaderInfo> & Package::shaders() const
{
    return m_shaders;
}

}
