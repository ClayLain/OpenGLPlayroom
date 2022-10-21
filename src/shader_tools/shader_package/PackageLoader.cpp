#include "PackageLoader.h"

#include <quazip/quazipfile.h>

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace shaders
{

tl::expected<Type, error_handling::Error> parseShaderType(const QString &string)
{
    static const auto stringToTypeMap = std::map<QString, Type> {
        { "vertex", Type::Vertex },
        { "fragment", Type::Fragment },
    };

    const auto it = stringToTypeMap.find(string.toLower());
    if (it == stringToTypeMap.cend()) {
        return tl::unexpected { error_handling::Error { "Can't parse shader type: " + string.toStdString() } };
    }

    return it->second;
}

tl::expected<Package, error_handling::Error> PackageLoader::load(const std::string &path)
{
    m_archive.setZipName(QString::fromStdString(path));
    if(!m_archive.open(QuaZip::mdUnzip)) {
        return tl::unexpected { error_handling::Error { "Can't open shader package file" } };
    }

    const auto manifestContent = readFileContent("manifest.json");
    if (!manifestContent) {
        return tl::unexpected { manifestContent.error() };
    }
    return parseManifest(manifestContent.value());
}

tl::expected<QString, error_handling::Error> PackageLoader::readFileContent(const QString &path)
{
    auto currentArchivedFile = QuaZipFile { &m_archive };
    const auto manifestFileExist = m_archive.setCurrentFile(path, QuaZip::CaseSensitivity::csInsensitive);
    if (!manifestFileExist) {
        return tl::unexpected { error_handling::Error { "Shader package file missed: " + path.toStdString() } };
    }

    currentArchivedFile.open(QIODevice::ReadOnly);
    const auto manifestContent = currentArchivedFile.readAll();
    if (manifestContent.isEmpty()) {
        return tl::unexpected { error_handling::Error { "Can't read package file content: " + path.toStdString() } };
    }

    return manifestContent;
}

tl::expected<ShaderInfo, error_handling::Error> PackageLoader::parseShaderInfo(const QJsonObject &object)
{
    const auto type = parseShaderType(object["type"].toString());
    if (!type.has_value()) {
        return tl::unexpected { type.error() };
    }

    const auto pathString = object["path"].toString();
    const auto shaderContent = readFileContent(pathString);
    if (!shaderContent.has_value()) {
        return tl::unexpected { shaderContent.error() };
    }

    ShaderInfo result;
    result.type = type.value();
    result.content = shaderContent.value().toStdString();
    return result;
}

tl::expected<Package, error_handling::Error> PackageLoader::parseManifest(const QString &manifestContent)
{
    auto parseError = QJsonParseError {};
    const auto manifestDocument = QJsonDocument::fromJson(manifestContent.toUtf8(), &parseError);
    if (parseError.error) {
        return tl::unexpected { error_handling::Error { "Can't parse json: " + parseError.errorString().toStdString() } };
    }

    if (!manifestDocument.isObject()) {
        return tl::unexpected { error_handling::Error { "Manifest root is not object" } };
    }

    const auto rootObject = manifestDocument.object();
    const auto idString = rootObject["id"].toString().toStdString();
    const auto idOpt = shaders::PackageId::from_string(idString);
    if (!idOpt.has_value()) {
        return tl::unexpected { error_handling::Error { "Invalid package id: " + idString } };
    }

    const auto versionString = rootObject["version"].toString().toStdString();
    const auto versionOpt = semver::from_string_noexcept(versionString);
    if (!versionOpt.has_value()) {
        return tl::unexpected { error_handling::Error { "Invalid package version: " + versionString } };
    }

    auto shaders = std::vector<ShaderInfo> {};
    const auto shadersJsonValue = rootObject["shaders"];
    if (!shadersJsonValue.isArray()) {
        return tl::unexpected { error_handling::Error { "Shaders value is not array" } };
    }

    const auto shadersJsonArray = shadersJsonValue.toArray();
    for (const auto &shaderInfoItem : shadersJsonArray) {
        const auto result = parseShaderInfo(shaderInfoItem.toObject());
        if (!result.has_value()) {
            return tl::unexpected { result.error() };
        }
        shaders.push_back(result.value());
    }

    return Package { idOpt.value(), versionOpt.value(), shaders };
}

}
