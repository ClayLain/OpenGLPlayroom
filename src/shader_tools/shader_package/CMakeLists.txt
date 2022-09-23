set(public_headers
    Error.h
    Package.h
    PackageLoader.h
)

set(source
    Error.cpp
    Package.cpp
    PackageLoader.cpp
)

add_library(shader_package STATIC ${source} ${public_headers})
target_link_libraries(shader_package
    PUBLIC stduuid semver expected QuaZip::QuaZip
)

create_includedir(TARGET shader_package DIR shader_package HEADERS ${public_headers})
