#!env python

import argparse
import os.path
import zipfile
import json


class StartupInfo:
    def __init__(self, id, version, destination, fshaders, vshaders):
        self.id = id
        self.version = version
        self.fshaders = fshaders
        self.vshaders = vshaders
        self.destination = os.path.normpath(destination).replace("\\","/")

        for file in self.fshaders:
            assert os.path.exists(file), "Fragment shader source file is missing: " + file

        for file in self.vshaders:
            assert os.path.exists(file), "Vertex shader source file is missing: " + file


def parse_arguments():
    parser = argparse.ArgumentParser(description="Pack a set of shader files into one package.")
    parser.add_argument("--id",
                        type=str,
                        help="Unique package identifier. UUID format required",
                        required=True
                        )
    parser.add_argument("--version",
                        type=str,
                        help="Version of vertex package. Semver format required",
                        required=True
                        )
    parser.add_argument("--destination",
                        type=str,
                        help="Path to the folder where the result will be placed",
                        required=True
                        )
    parser.add_argument("--fshaders",
                        type=str,
                        nargs="+",
                        help="List of files with fragment shader code to package",
                        required=True
                        )
    parser.add_argument("--vshaders",
                        type=str,
                        nargs="+",
                        help="List of files with vertex shader code to package",
                        required=True
                        )
    args = parser.parse_args()
    return StartupInfo(args.id, args.version, args.destination, args.fshaders, args.vshaders)


def create_manifest_shader_data(shader_files, type):
    result = []
    for file in shader_files:
        result.append({ 
            "type": type,
            "path": "shaders/" + os.path.basename(file) 
            })
    return result


def create_manifest(id, version, package_name, fshaders, vshaders):
    fshaders_data = create_manifest_shader_data(fshaders, "fragment")
    vshaders_data = create_manifest_shader_data(vshaders, "vertex")
    data = {
        "id": id,
        "version": version,
        "shaders": fshaders_data + vshaders_data
    }
    return json.dumps(data)


def zip_package(archive, manifest, files):
    archive.writestr("manifest.json", manifest)
    for file in files:
        archive.write(file, "shaders/" + os.path.basename(file))


if __name__ == '__main__':
    parsed_args = parse_arguments()    
    file = zipfile.ZipFile(parsed_args.destination, 
        mode='w', 
        compression=zipfile.ZIP_DEFLATED, 
        compresslevel=9
        )
    manifest = create_manifest(
        parsed_args.id, 
        parsed_args.version, 
        os.path.basename(parsed_args.destination), 
        parsed_args.fshaders, 
        parsed_args.vshaders
        )
    zip_package(file, manifest, parsed_args.fshaders + parsed_args.vshaders)
    file.close()
