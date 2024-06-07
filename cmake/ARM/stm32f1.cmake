
set(ARCH_COMPILE_DEFS
        ${ARCH_COMPILE_DEFS}
        "-DSTM32F1"
)

set(ARCH_INCLUDES
        ${ARCH_INCLUDES}

        "${CMAKE_SOURCE_DIR}/third_party/cmsis_device_stm32f1/Include"
)

set(ARCH_SOURCES
        ${ARCH_SOURCES}

        "${CMAKE_SOURCE_DIR}/third_party/cmsis_device_stm32f1/Source/Templates/system_stm32f1xx.c"
)


include(${CMAKE_CURRENT_LIST_DIR}/arm_m3.cmake)
