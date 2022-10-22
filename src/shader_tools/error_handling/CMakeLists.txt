set(public_headers
    error.h
)

set(source
    error.cpp
)

add_library(error_handling STATIC ${source} ${public_headers})
target_link_libraries(error_handling PUBLIC expected)

create_includedir(TARGET error_handling DIR error_handling HEADERS ${public_headers})
