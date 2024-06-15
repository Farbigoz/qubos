set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_EXECUTABLE_SUFFIX ".elf")


set(ARCH_COMPILE_OPTIONS
        ${ARCH_COMPILE_OPTIONS}

        "-ffunction-sections"   # Remove unused code
        "-fdata-sections"       # Remove unused code
        "-fno-common"           # C++ compatibility
        "-fno-exceptions"       # Disable C++ exceptions
        "-fmessage-length=0"
        "-ggdb3"                # GDB debugger
        "-fno-rtti"             # C++ abstract class remove rtti
        "-fno-unwind-tables"    # C++ abstract class remove unwind tables
)
