set(public_headers
    Package.h
    PackageLoader.h
)

set(source
    Package.cpp
    PackageLoader.cpp
)

add_library(shader_package STATIC ${source} ${public_headers})
target_link_libraries(shader_package
    PUBLIC QuaZip::QuaZip
    PUBLIC error_handling
    PUBLIC expected
    PUBLIC semver
    PUBLIC stduuid
)

create_includedir(TARGET shader_package DIR shader_package HEADERS ${public_headers})
