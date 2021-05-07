

function(set_project_warnings project_name)
  target_compile_options(${project_name} BEFORE
    INTERFACE
      $<$<C_COMPILER_ID:Clang>:-Wcast-align
                               -Wcast-qual
                               -Wconversion
                               -Wexit-time-destructors
                               -Wglobal-constructors
                               -Wmissing-noreturn
                               -Wmissing-prototypes
                               -Wno-missing-braces
                               -Wold-style-cast
                               -Wshadow
                               -Wweak-vtables
                               -Werror
                               -Wall>
      $<$<C_COMPILER_ID:GNU>:-Waddress
                             -Wformat-nonliteral
                             -Wformat-security
                             -Wformat
                             -Winit-self
                             # TODO: We want this for the regular build, and not for UT
                             #-Wmissing-declarations
                             -Wmissing-include-dirs
                             -Wno-multichar
                             -Wno-parentheses
                             -Wno-type-limits
                             -Wno-unused-parameter
                             -Wunreachable-code
                             -Wwrite-strings
                             -Wpointer-arith
                             -Werror
                             -Wall>
     $<$<C_COMPILER_ID:MSVC>:/Wall>
)

endfunction()
