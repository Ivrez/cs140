/* main.c */

#include "rpi.h"

void main(void) {
    int led = 20;
    gpio_set_output(led);
    for(int i = 0; i < 10; i++) {
        gpio_set_on(led);
        delay_cycles(1000000);
        gpio_set_off(led);
        delay_cycles(1000000);
    }
}