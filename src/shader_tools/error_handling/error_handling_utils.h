#pragma once

#include <stdexcept>

#include "error.h"

namespace error_handling
{

class FatalErrorHandlerCalled : public std::runtime_error
{
public:
    explicit FatalErrorHandlerCalled(const Error &error);
};

void fatalError(const Error &error);

}
