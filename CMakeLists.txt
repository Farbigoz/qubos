cmake_minimum_required(VERSION 3.16)

project(
    system
    VERSION 0.0.1
    LANGUAGES C CXX ASM
)


add_library(system)

target_include_directories(system
    PUBLIC
        #"$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>"
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_sources(system
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/system/system.cpp
)


add_subdirectory(examples/example)
