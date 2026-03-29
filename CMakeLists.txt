cmake_minimum_required(VERSION 3.13)

include(pico-sdk/external/pico_sdk_import.cmake)

project(multi_project)

pico_sdk_init()

add_subdirectory(fatfs/FatFs_SPI)

file(GLOB APP_SOURCES "*.c")

# 🔥 tránh build hw_config thành app
list(REMOVE_ITEM APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/hw_config.c)

foreach(src ${APP_SOURCES})
    get_filename_component(name ${src} NAME_WE)

    add_executable(${name}
        ${src}
        hw_config.c   # 🔥 quan trọng
    )

    target_link_libraries(${name}
        pico_stdlib
        hardware_spi
        FatFs_SPI
    )

    pico_enable_stdio_usb(${name} 1)
    pico_enable_stdio_uart(${name} 0)

    pico_add_extra_outputs(${name})
endforeach()