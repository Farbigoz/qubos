

add_executable(example main.cpp sha1.c crc.c)
target_link_libraries(example PUBLIC system)
