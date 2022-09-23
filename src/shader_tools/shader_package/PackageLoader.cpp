#include "PackageLoader.h"

#include <JlCompress.h>

namespace shaders
{

tl::expected<Package, Error> PackageLoader::load(const std::string &path)
{
    // - manifest.json
    // -shaders
    // --shader1
    // --shader2
    // --shader3

    // manifest
    // {
    // "id"
    // "version"
    // shaders
    //   [
    //      { type, path }
    //      { type, path }
    //   ]
    // }

    // unpack archive
    // parse manifest file
    // load shader files

  //  const auto x = JlCompress::extractDir(QString::fromStdString(path));


    return {};
}

}
