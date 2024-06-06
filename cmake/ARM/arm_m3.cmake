include(${CMAKE_CURRENT_LIST_DIR}/embedded.cmake)



set(ARCH_COMPILE_DEFS
        ${ARCH_COMPILE_DEFS}

        # CMSIS DSP
        "-DARM_MATH_CM3"
        "-DARM_MATH_MATRIX_CHECK"
        "-DARM_MATH_ROUNDING"
)

set(ARCH_COMPILE_OPTIONS
        ${ARCH_COMPILE_OPTIONS}

        "-mcpu=cortex-m3"       # Cortex version
        "-mthumb"               # Use short commands
        "-mthumb-interwork"     # Use short commands
        "-ffunction-sections"   # Remove unused code
        "-fdata-sections"       # Remove unused code
        "-fno-common"           # C++ compatibility
        "-fno-exceptions"       # Disable C++ exceptions
        "-fmessage-length=0"

        "$<$<COMPILE_LANGUAGE:ASM>:-x$<SEMICOLON>assembler-with-cpp>"   # Enable assembler files preprocessing
)

set(ARCH_LINK_OPTIONS
        ${ARCH_LINK_OPTIONS}

        "-Wl,-gc-sections,--print-memory-usage,-Map=${PROJECT_NAME}.map"
        "-mcpu=cortex-m3"
        "-mthumb"
        "-mthumb-interwork"
        "-T" "${ARCH_LINK_SCRIPT}"

        "--specs=nosys.specs"
        "--specs=nano.specs"
)

set(ARCH_FREERTOS_PORT
        GCC_ARM_CM4F
)

set(ARCH_INCLUDES
        ${ARCH_INCLUDES}

        "${CMAKE_SOURCE_DIR}/third_party/CMSIS_5/CMSIS/Core/Include"
)

set(ARCH_SOURCES
        ${ARCH_SOURCES}

        "${CMAKE_SOURCE_DIR}/arch/ARM/crt0.s"
        "${CMAKE_SOURCE_DIR}/arch/ARM/irq.c"
        "${CMAKE_SOURCE_DIR}/arch/ARM/irq.cpp"
)

set(ARCH_LIBRARIES
        ${ARCH_LIBRARIES}

        CMSISDSP
)



# Import CMSIS-DSP
add_subdirectory(${CMAKE_SOURCE_DIR}/third_party/CMSIS-DSP)

target_include_directories(CMSISDSP
        PUBLIC
        ${ARCH_INCLUDES}
)
target_compile_options(CMSISDSP
        PUBLIC
        ${ARCH_LINK_OPTIONS}
)
