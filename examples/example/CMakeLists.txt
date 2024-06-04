

# add_executable(example main.cpp sha1.c crc.c)
add_executable(example main_arm.cpp)
target_link_libraries(example PUBLIC system)
