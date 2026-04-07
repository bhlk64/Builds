#include "pico/stdlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ff.h"
#include "hw_config.h"

#define LED_PIN 25;

void fail(int f) {
    while (f) {
        gpio_put(LED_PIN, 1);
        sleep_ms(200);
        gpio_put(LED_PIN, 0);
        sleep_ms(200);
        f--;
    }
    while(1);
}

int main() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    FATFS fs;
    FRESULT fr = f_mount(&fs, "", 1);
    
    //FILE *f = fopen("times.txt","r");
    
    if (fr!=FR_OK) {fail(1);}
    
    FIL f;
    char buf[16];
    int times;
    if (f_open(&f,"times.txt",FA_READ)==FR_OK) {
        if (f_gets(buf, sizeof(buf),&f)) {
            times = atoi(buf);
        }
    }
    
    f_close(&f);

    while (times) {
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
        times--;
    }
    while(1);
}
