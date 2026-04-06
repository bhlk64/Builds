#include "pico/stdlib.h"

int main() {
    const uint LED_PIN = 25;  // onboard LED
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    
    FILE *f = fopen("times.txt","r");
    
    if (f==NULL) {
        gpio_put(LED_PIN,1);
        while(1);
    }
    
    int times;
    fscanf(f,"%d",&times);
    fclose(f);

    while (times) {
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
    }
    while(1);
}