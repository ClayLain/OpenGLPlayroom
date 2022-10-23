#pragma once

#include <cxxopts.hpp>
#include <error_handling/error.h>

namespace argument_parser
{

struct ProgramOptions
{
    std::string filePath;
};

error_handling::Result<ProgramOptions> parse(int argc, char *argv[]);

}
