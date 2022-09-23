#pragma once

#include <string>

namespace shaders
{

class Error
{
    Error(const std::string &description);

    std::string description() const;

private:
    std::string m_description;
};

}
