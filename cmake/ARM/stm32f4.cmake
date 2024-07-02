
set(ARCH_COMPILE_DEFS
        ${ARCH_COMPILE_DEFS}
        "-DSTM32F4"
)

set(ARCH_INCLUDES
        ${ARCH_INCLUDES}

        "${CMAKE_SOURCE_DIR}/third_party/cmsis_device_stm32f4/Include"
        "${CMAKE_SOURCE_DIR}/third_party/stm32f4xx_hal_driver/Inc"
)

set(ARCH_SOURCES
        ${ARCH_SOURCES}

        "${CMAKE_SOURCE_DIR}/third_party/cmsis_device_stm32f4/Source/Templates/system_stm32f4xx.c"

        "${CMAKE_SOURCE_DIR}/third_party/stm32f4xx_hal_driver/Src/stm32f4xx_hal_can.c"
        "${CMAKE_SOURCE_DIR}/impl/STM32/HAL/hal.cpp"
)


include(${CMAKE_CURRENT_LIST_DIR}/arm_m4.cmake)
