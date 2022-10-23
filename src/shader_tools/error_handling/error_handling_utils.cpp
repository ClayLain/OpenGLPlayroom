#include "error_handling_utils.h"

#include "log.h"

namespace error_handling
{

FatalErrorHandlerCalled::FatalErrorHandlerCalled(const Error &error)
    : std::runtime_error(error.description())
{
}

void fatalError(const Error &error)
{
    log(error.description(), Level::Error);
    throw FatalErrorHandlerCalled(error);
}

}
