#include "pico/stdlib.h"

#define LED_PIN 25  // onboard LED
#define BTN_PIN 0

int main() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    gpio_init(BTN_PIN);
    gpio_set_dir(BTN_PIN, GPIO_IN);
    gpio_pull_down(BTN_PIN); // đảm bảo không bập bùng

    while(1) {
        if(gpio_get(BTN_PIN)) {
            gpio_put(LED_PIN, 1);
        } else {
            gpio_put(LED_PIN, 0);
        }
    }
}