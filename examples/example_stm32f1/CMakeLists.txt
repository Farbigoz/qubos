
# target_compile_definitions(system
#     PUBLIC
#         "-DHAL_ETH_MODULE_ENABLED"
# )

target_include_directories(system
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}"
        "${CMAKE_CURRENT_LIST_DIR}/lwip"
        "${CMAKE_SOURCE_DIR}/third_party/lwip/src/include"
        "${CMAKE_SOURCE_DIR}/third_party/stm32f1xx_hal_driver/Inc"
)

file(GLOB_RECURSE lwip_sources
        "${CMAKE_SOURCE_DIR}/third_party/lwip/src/api/*.c"
        "${CMAKE_SOURCE_DIR}/third_party/lwip/src/core/*.c"
        "${CMAKE_SOURCE_DIR}/third_party/lwip/src/netif/*.c"
)

target_sources(system
    PUBLIC
        "${CMAKE_SOURCE_DIR}/third_party/stm32f1xx_hal_driver/Src/stm32f1xx_hal_can.c"
        "${CMAKE_SOURCE_DIR}/third_party/stm32f1xx_hal_driver/Src/stm32f1xx_hal_eth.c"
        "${CMAKE_SOURCE_DIR}/third_party/stm32f1xx_hal_driver/Src/stm32f1xx_hal_rcc.c"
        "${CMAKE_SOURCE_DIR}/third_party/stm32f1xx_hal_driver/Src/stm32f1xx_hal_gpio.c"
        "${CMAKE_CURRENT_LIST_DIR}/lwip/ethernetif.c"
        "${CMAKE_CURRENT_LIST_DIR}/lwip/lwip.c"
        ${lwip_sources}
)

# add_executable(example main.cpp sha1.c crc.c)
add_executable(example main_stm32f1.cpp)
# add_executable(example main_stm32f1.cpp)
target_link_libraries(example PUBLIC system)
