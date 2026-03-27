cmake_minimum_required(VERSION 3.13)
include(pico_sdk_import.cmake)

project(blink_project)

# Initialize Pico SDK
pico_sdk_init()

# Add executable
add_executable(blink blink.c)

# Link standard library
target_link_libraries(blink pico_stdlib)

# Enable UF2 output
pico_add_extra_outputs(blink)