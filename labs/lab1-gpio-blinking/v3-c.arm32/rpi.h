#ifndef __RPI_H__
#define __RPI_H__

typedef unsigned int uint;

#define GPIO_CNT 26 // rpi 3b gpio count

uint get_fsel_addr(int gpio_pin);

void gpio_set_output(int gpio_pin);

void gpio_set_on(int gpio_pin);

void gpio_set_off(int gpio_pin);

void delay(int count);

#endif