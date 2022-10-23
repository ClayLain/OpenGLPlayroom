#pragma once

#include <string>

#include <error_handling/error.h>

namespace file_utils
{

error_handling::Result<std::string> readTextFileContent(const std::string &path);

}
