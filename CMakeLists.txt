cmake_minimum_required(VERSION 3.13)

include(pico-sdk/external/pico_sdk_import.cmake)

project(multi_project)

pico_sdk_init()

# 🔥 add FatFS lib
add_subdirectory(fatfs/FatFs_SPI)
# add_subdirectory(fatfs/example)

# 🔥 App sources
file(GLOB APP_SOURCES "*.c")

foreach(src ${APP_SOURCES})
    get_filename_component(name ${src} NAME_WE)

    add_executable(${name} ${src})

    target_link_libraries(${name}
        pico_stdlib
        hardware_spi
        FatFs_SPI
        hw_config.c
    )

    pico_enable_stdio_usb(${name} 1)
    pico_enable_stdio_uart(${name} 0)

    pico_add_extra_outputs(${name})
endforeach()