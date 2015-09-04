# Icicle

cmake_minimum_required (VERSION 2.8.12)

project (icicle)

# Compiler flags

if (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)
    add_compile_options (-static)
    set (CMAKE_CXX_FLAGS "-std=c++14")
endif (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_GNUCC)

if (MSVC)
    add_compile_options (/MT)
endif (MSVC)

# Add files

file (GLOB icicle_source ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/source/detail/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/include/detail/*.hpp)
add_library (icicle ${icicle_source})
target_include_directories(icicle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set (icicle_include_directories ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include ${CMAKE_CURRENT_SOURCE_DIR}external/glm ${CMAKE_CURRENT_SOURCE_DIR}external/stb ${CMAKE_CURRENT_SOURCE_DIR}/external/tinyobjloader/include)

# Options

set (BUILD_SHARED_LIBS OFF CACHE BOOL "")

# Link GLAD

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/external/glad)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include)
target_link_libraries (icicle glad)

# GLFW Options

set (GLFW_BUILD_DOCS FALSE CACHE BOOL "")
set (GLFW_BUILD_EXAMPLES FALSE CACHE BOOL "")
set (GLFW_BUILD_TESTS FALSE CACHE BOOL "")

# Link GLFW

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/external/glfw-3.1.1)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/external/glfw-3.1.1/include)
target_link_libraries (icicle glfw ${GLFW_LIBRARIES}) # This links OpenGL amd GLFW's other dependencies.

# Link tinyobjloader

add_subdirectory (${CMAKE_CURRENT_SOURCE_DIR}/external/tinyobjloader)
include_directories (${CMAKE_CURRENT_SOURCE_DIR}/external/tinyobjloader/include)
target_link_libraries (icicle tinyobjloader)

# Include GLM

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/glm-0.9.6.3)

# Include STB

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/stb)
