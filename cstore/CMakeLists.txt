
##### Vector #####
add_library(cstore_vector
   src/vector.c)

target_include_directories(cstore_vector
   PUBLIC includes)

target_link_libraries(cstore_vector
   PRIVATE project_warnings
   PRIVATE project_options)

##### Ring Buffer #####
add_library(cstore_ring_buffer
   src/ring_buffer.c)

target_include_directories(cstore_ring_buffer
   PUBLIC includes)

target_link_libraries(cstore_ring_buffer
   PRIVATE project_warnings
   PRIVATE project_options)

##### cstore #####
add_library(cstore INTERFACE)

target_link_libraries(cstore
   INTERFACE
      cstore_vector
      cstore_ring_buffer)
