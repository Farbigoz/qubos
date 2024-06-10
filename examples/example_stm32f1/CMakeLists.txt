

# add_executable(example main.cpp sha1.c crc.c)
add_executable(example main_stm32f1.cpp)
# add_executable(example main_stm32f1.cpp)
target_link_libraries(example PUBLIC system)
