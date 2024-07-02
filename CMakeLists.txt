cmake_minimum_required(VERSION 3.16)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_SYSTEM_NAME Generic)

project(
        system
        VERSION 0.0.1
        LANGUAGES C CXX ASM
)

# include(${CMAKE_SOURCE_DIR}/cmake/ARM/stm32f401.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/ARM/stm32f405.cmake)
# include(${CMAKE_SOURCE_DIR}/cmake/ARM/stm32f107.cmake)

add_library(system STATIC)

target_sources(system
    PUBLIC
        ${ARCH_SOURCES}
        ${CMAKE_CURRENT_LIST_DIR}/system/syscalls.c
        ${CMAKE_CURRENT_LIST_DIR}/system/sysmem.c
        ${CMAKE_CURRENT_LIST_DIR}/system/system.cpp
)

target_include_directories(system
    PUBLIC
        ${ARCH_INCLUDES}
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_compile_definitions(system
    PUBLIC
        ${ARCH_COMPILE_DEFS}
)

target_compile_options(system
    PUBLIC
        ${ARCH_COMPILE_OPTIONS}
)

target_link_options(system
    PUBLIC
        ${ARCH_LINK_OPTIONS}
)

target_link_libraries(system
    PUBLIC
        ${ARCH_LIBRARIES}
)



add_subdirectory(examples/example)
# add_subdirectory(examples/example_stm32f1)
