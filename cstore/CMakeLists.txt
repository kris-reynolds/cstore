
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

##### List #####
add_library(cstore_list
src/list.c)

target_include_directories(cstore_list
   PUBLIC includes)

target_link_libraries(cstore_list
   PUBLIC cstore_fixed_pool
   PRIVATE project_warnings
   PRIVATE project_options)

##### Pool #####
add_library(cstore_fixed_pool
   src/pool.c)

target_include_directories(cstore_fixed_pool
   PUBLIC includes)

target_link_libraries(cstore_fixed_pool
   PRIVATE project_warnings
   PRIVATE project_options)

##### cstore #####
add_library(cstore INTERFACE)

target_link_libraries(cstore
   INTERFACE
      cstore_vector
      cstore_ring_buffer
      cstore_list)
