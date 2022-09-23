#include "Error.h"

namespace shaders
{

Error::Error(const std::string &description)
    : m_description(description)
{
}

std::string Error::description() const
{
    return m_description;
}

}
