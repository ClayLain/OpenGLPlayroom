#include "file_utils.h"

#include <fstream>

namespace file_utils
{

error_handling::Result<std::string> readTextFileContent(const std::string &path)
{
    auto stream = std::ifstream(path);
    if (!stream.is_open()) {
        return tl::unexpected { error_handling::Error { "Can't open file: " + path } };
    } else {
        return std::string(std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>());
    }
}

}
