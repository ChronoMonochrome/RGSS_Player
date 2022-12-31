add_executable(hello WIN32)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "*.cpp"
)

target_sources(hello PRIVATE ${SRC_FILES})

if(${CMAKE_CXX_COMPILER_ID} MATCHES "MSVC")
    target_compile_options(hello PUBLIC "/std:c++latest")
else()
    target_compile_options(hello PUBLIC "-std=c++17")
endif()

target_include_directories(hello PUBLIC include)

target_link_libraries(hello
  PRIVATE
    fmt::fmt
)