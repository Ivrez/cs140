/* main.c */

#include "rpi.h"

int main(void) {
    int led1 = 21;
    int led2 = 20;

    gpio_set_output(led1);
    gpio_set_output(led2);

    for(int i = 0; i < 10; i++) {
        gpio_set_on(led1);
        gpio_set_on(led2);
        delay(100000);
        gpio_set_off(led1);
        gpio_set_off(led2);
        delay(100000);
    }
}
