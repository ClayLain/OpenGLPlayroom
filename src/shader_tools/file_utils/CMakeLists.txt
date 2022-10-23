set(public_headers
    file_utils.h
)

set(source
    file_utils.cpp
)

add_library(file_utils STATIC ${source} ${public_headers})
target_link_libraries(file_utils PUBLIC expected error_handling)

create_includedir(TARGET file_utils DIR file_utils HEADERS ${public_headers})
