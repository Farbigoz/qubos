
set(ARCH_COMPILE_DEFS
        ${ARCH_COMPILE_DEFS}
        "-DSTM32F107xC"
)

set(ARCH_LINK_SCRIPT
        "${CMAKE_SOURCE_DIR}/linker/STM32F107VCTX_FLASH.ld"
)

set(ARCH_SOURCES
        ${ARCH_SOURCES}

        # "${CMAKE_SOURCE_DIR}/third_party/cmsis_device_stm32f1/Source/Templates/gcc/startup_stm32f107xc.s"
)


include(${CMAKE_CURRENT_LIST_DIR}/stm32f3.cmake)
