#pragma once

#include <string>

#include <tl/expected.hpp>

namespace error_handling
{

#define CHECK_AND_RETURN(RESULT)                  \
    if (!RESULT.has_value()) {                    \
        return tl::unexpected { RESULT.error() }; \
    }

class Error
{
public:
    Error(const std::string &description);

    std::string description() const;

private:
    std::string m_description;
};

template <typename T>
using Result = tl::expected<T, Error>;

}
