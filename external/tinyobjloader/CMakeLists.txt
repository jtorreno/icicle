cmake_minimum_required (VERSION 2.8)

project (tinyobjloader)

add_library (tinyobjloader ${CMAKE_CURRENT_SOURCE_DIR}/source/tiny_obj_loader.cc)

target_include_directories (tinyobjloader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)