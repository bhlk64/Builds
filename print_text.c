#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "lib/hd44780pcf8574.h"

#define I2C_PORT i2c0
#define SDA_PIN 4
#define SCL_PIN 5

int main() {
    stdio_init_all();

    // 🔌 Init I2C
    i2c_init(I2C_PORT, 100 * 1000); // 100kHz
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    sleep_ms(200); // chờ ổn định

    // 📺 Init LCD
    HD44780_PCF8574_Init();
    HD44780_PCF8574_DisplayOn();
    HD44780_PCF8574_DisplayClear();

    int num = 0;

    while (1) {
        char buf[16];
        sprintf(buf, "Num: %d", num);

        // dòng 1
        HD44780_PCF8574_PositionXY(0, 0);
        HD44780_PCF8574_DrawString("Hello bro 😎");

        // dòng 2
        HD44780_PCF8574_PositionXY(0, 1);
        HD44780_PCF8574_DrawString(buf);

        num++;

        sleep_ms(1000);
    }
}