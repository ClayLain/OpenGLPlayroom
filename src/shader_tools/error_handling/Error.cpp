#include "error.h"

namespace error_handling
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
