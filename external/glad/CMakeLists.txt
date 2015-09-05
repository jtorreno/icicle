cmake_minimum_required (VERSION 2.8)

project (glad)

add_library (glad ${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c)

if (UNIX)
    target_link_libraries (glad dl)
endif (UNIX)

target_include_directories (glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
