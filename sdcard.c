#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "ff.h"
#include "hw_config.h"

#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19

int main() {
    stdio_init_all();

    spi_init(SPI_PORT, 1000 * 1000);

    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);

    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);

    FATFS fs;
    FRESULT fr = f_mount(&fs, "", 1);

    if (fr != FR_OK) {
        printf("Mount fail\n");
        while (1);
    }

    FIL fil;
    UINT bw; // bytes written

    // 🔥 MỞ FILE ĐỂ GHI (tạo mới nếu chưa có)
    fr = f_open(&fil, "hello.txt", FA_WRITE | FA_CREATE_ALWAYS);

    if (fr == FR_OK) {
        const char *text = "hello from RP2040 😎\n";

        fr = f_write(&fil, text, strlen(text), &bw);

        if (fr == FR_OK) {
            printf("Write OK (%d bytes)\n", bw);
        } else {
            printf("Write fail\n");
        }

        f_close(&fil);
    } else {
        printf("Open fail\n");
    }

    while (1);
}