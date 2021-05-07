

add_library(cstore
   src/vector.c)

target_include_directories(cstore
   PUBLIC includes)

target_link_libraries(cstore
    PRIVATE project_warnings
    PRIVATE project_options)
