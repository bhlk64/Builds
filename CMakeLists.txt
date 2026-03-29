cmake_minimum_required(VERSION 3.13)

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(multi_project)

pico_sdk_init()

# 🔥 lấy tất cả file .c
file(GLOB SRC_FILES "*.c")

foreach(src ${SRC_FILES})
    # lấy tên file (không có .c)
    get_filename_component(name ${src} NAME_WE)

    add_executable(${name} ${src})

    target_link_libraries(${name} pico_stdlib)

    pico_enable_stdio_usb(${name} 1)
    pico_enable_stdio_uart(${name} 0)

    pico_add_extra_outputs(${name})
endforeach()