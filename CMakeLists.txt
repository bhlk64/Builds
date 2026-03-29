cmake_minimum_required(VERSION 3.13)

include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(multi_project)

pico_sdk_init()

# 🔥 App sources (blink.c, sdcard.c,...)
file(GLOB APP_SOURCES "*.c")

# 🔥 FatFS + SD driver
file(GLOB FATFS_SRC "lib/fatfs/*.c")

foreach(src ${APP_SOURCES})
    get_filename_component(name ${src} NAME_WE)

    add_executable(${name} ${src} ${FATFS_SRC})

    target_include_directories(${name} PRIVATE lib/fatfs)

    target_link_libraries(${name}
        pico_stdlib
        hardware_spi
    )

    pico_enable_stdio_usb(${name} 1)
    pico_enable_stdio_uart(${name} 0)

    pico_add_extra_outputs(${name})
endforeach()