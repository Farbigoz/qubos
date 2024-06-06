
set(ARCH_INCLUDES
        ${ARCH_INCLUDES}

        "${CMAKE_SOURCE_DIR}/third_party/cmsis_device_stm32f4/Include"
)

set(ARCH_SOURCES
        ${ARCH_SOURCES}

        "${CMAKE_SOURCE_DIR}/third_party/cmsis_device_stm32f4/Source/Templates/system_stm32f4xx.c"
)


include(${CMAKE_CURRENT_LIST_DIR}/arm_m4.cmake)
