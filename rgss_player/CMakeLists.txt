add_executable(rgss_player WIN32)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "*.cpp"
)

target_sources(rgss_player PRIVATE ${SRC_FILES})

target_compile_options(rgss_player PUBLIC "/std:c++latest")

target_include_directories(rgss_player PUBLIC include)

target_link_libraries(rgss_player
  PRIVATE
    fmt::fmt
)
