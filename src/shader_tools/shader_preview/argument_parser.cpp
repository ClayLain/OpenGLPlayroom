#include "argument_parser.h"

#include "application_strings.h"

namespace argument_parser
{

error_handling::Result<ProgramOptions> parse(int argc, char *argv[])
{
    cxxopts::Options options(application_strings::g_applicationName, application_strings::g_applicationDescr);
    options.add_option("", "f", "file", application_strings::g_fileOptionDescr, cxxopts::value<std::string>(), "");
    const auto result = options.parse(argc, argv);
    if (result.count("file") == 0) {
        return tl::unexpected { error_handling::Error { "Option 'file' is missed in command line" } };
    }

    return ProgramOptions {
        result["file"].as<std::string>()
    };
}

}
