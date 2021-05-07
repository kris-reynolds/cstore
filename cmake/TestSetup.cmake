

include(ExternalProject)


enable_testing()

ExternalProject_Add(unitytest
  GIT_REPOSITORY    https://github.com/ThrowTheSwitch/Unity
  GIT_TAG           v2.5.2
  SOURCE_DIR        "${CMAKE_BINARY_DIR}/unity-src"
  INSTALL_COMMAND   cmake -E echo "Skipping install step."
)

ExternalProject_Get_Property(unitytest source_dir)
ExternalProject_Get_Property(unitytest binary_dir)
set(UNITY_INCLUDE_DIRS ${source_dir}/src)
set(UNITY_LIBRARY_PATH ${binary_dir}/${CMAKE_FIND_LIBRARY_PREFIXES}unity.a)
message(STATUS "UNITY VALUE ${UNITY_INCLUDE_DIRS}")
message(STATUS "UNITY VALUE ${UNITY_LIBRARY_PATH}")

add_library(unity UNKNOWN IMPORTED)
set_target_properties(unity PROPERTIES
  IMPORTED_LOCATION ${UNITY_LIBRARY_PATH}
  )
target_include_directories(unity INTERFACE ${UNITY_INCLUDE_DIRS})

add_dependencies(unity unitytest)

# Add additional UT specific compile flags
add_library(test_compile_options INTERFACE)
target_link_libraries(test_compile_options INTERFACE
  unity
  project_warnings
  project_options
  )

target_include_directories(test_compile_options INTERFACE
   ${unity_PUBLIC_HEADERS})
# TODO: Hook in Code Coverage flags, etc
target_compile_options(test_compile_options
INTERFACE
  $<$<C_COMPILER_ID:Clang>:>
  $<$<C_COMPILER_ID:GNU>:-Wno-missing-declarations>
  $<$<C_COMPILER_ID:MSVC>:>)

#! cstore_add_test : generate executable and add test to the ctest framework
#
# \argn: a list of optional arguments
# \arg:TEST_NAME Name of the test. Note that this function appends a ".test"
# \group:SRC SRC is a list of source files to compile the test executable
# \group:DEPENDENCIES DEPENDENCIES any additional targets that should be compiled before this one
# \group:LIBS (Optional) Any additional required libraries that need to be linked
# \group:DEFS (Optional)  Any additional compile definitions
# \group:CONFIG_FILES (Optional) Non-compiled files such as configuration items
#        Note: These need to be supplied with a full path
function(cstore_add_test)
   set(options)
   set(oneValueArgs TEST_NAME)
   set(multiValueArgs SRC INCLUDES DEPENDENCIES LIBS DEFINITIONS CONFIG_FILES)
   cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

   set(ARGS_TEST_NAME "${ARGS_TEST_NAME}.test")

   add_executable (${ARGS_TEST_NAME} ${ARGS_SRC})

   target_link_libraries(${ARGS_TEST_NAME} ${ARGS_LIBS} test_compile_options)

   if(DEFINED ARGS_DEFS)
      target_compile_definitions(${ARGS_TEST_NAME} PRIVATE ${ARGS_DEFS})
   endif()

   if(DEFINED ARGS_CONFIG_FILES)
      # Loop over all config files and generate symbolic links
      foreach(config_item ${ARGS_CONFIG_FILES})
         get_filename_component(short_file_name ${config_item} NAME)
         install_symlink(${config_item} ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${short_file_name})
      endforeach()
   endif()

   add_test(NAME ${ARGS_TEST_NAME}
            COMMAND ${ARGS_TEST_NAME}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

endfunction()
