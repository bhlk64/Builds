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
#define PIN_BTN 0
#define PIN_LED 25

int main() {
    stdio_init_all();

    spi_init(SPI_PORT, 1000 * 1000);

    gpio_set_function(PIN_MISO, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);
    gpio_set_function(PIN_SCK,  GPIO_FUNC_SPI);

    gpio_init(PIN_CS);
    gpio_set_dir(PIN_CS, GPIO_OUT);
    gpio_put(PIN_CS, 1);
    
    gpio_init(PIN_BTN);
    gpio_set_dir(PIN_BTN, GPIO_IN);
    gpio_pull_up(PIN_BTN);
    
    gpio_init(PIN_LED);
    gpio_set_dir(PIN_LED, GPIO_OUT);

    FATFS fs;
    FRESULT fr = f_mount(&fs, "", 1);

    if (fr != FR_OK) {
        printf("Mount fail\n");
        while (1);
    }

    FIL fil;
    UINT bw; // bytes written

    // 🔥 MỞ FILE ĐỂ GHI (tạo mới nếu chưa có)
    // fr = f_open(&fil, "hello.txt", FA_WRITE | FA_CREATE_ALWAYS);
    
    int last_press = 0;
    int num = 1;

    while(1) {
        //fr = f_open(&fil, "hello.txt", FA_WRITE | FA_CREATE_ALWAYS);
        
        if (gpio_get(PIN_BTN) == 0) {
            fr = f_open(&fil, "hello.txt", FA_WRITE | FA_OPEN_ALWAYS);
            if (fr == FR_OK && last_press == 0) {
                f_lseek(&fil, f_size(&fil));
                // const char *text = "hello from RP2040 😎\n";
                char buf[16];
                int len = sprintf(buf, "%d\r\n", num);  // chuyển int → string + xuống dòng
                fr = f_write(&fil, buf, len, &bw);
        
                if (fr == FR_OK) {
                    gpio_put(PIN_LED, 1);
                }
        
                f_close(&fil);
                num = num + 1;
            } else {
                gpio_put(PIN_LED, 0);
            }
        }
        last_press = gpio_get(PIN_BTN);
        sleep_ms(10);
    }
}