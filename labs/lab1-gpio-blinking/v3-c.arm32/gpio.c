#include "rpi.h"

enum rpiRegisters {
    GPIO_BASE = 0x3f000000 + 0x200000,
    gpio_fsel0 = (GPIO_BASE + 0x00),
    gpio_fsel1 = (GPIO_BASE + 0x04),
    gpio_fsel2 = (GPIO_BASE + 0x08),
    gpio_fsel3 = (GPIO_BASE + 0x0C),
    gpio_set0  = (GPIO_BASE + 0x1C),
    gpio_clr0  = (GPIO_BASE + 0x28),
    gpio_lev0  = (GPIO_BASE + 0x34),
};

enum fselOutputMASK {
  f0 = 0x00000001,
  f1 = 0x00000008,
  f2 = 0x00000040,
  f3 = 0x00000200,
  f4 = 0x00001000,
  f5 = 0x00008000,
  f6 = 0x00040000,
  f7 = 0x00200000,
  f8 = 0x01000000,
  f9 = 0x08000000,
};

uint get_fsel_addr(int gpio_pin) {
    if(gpio_pin < 1 || gpio_pin > GPIO_CNT)
        return 0;

    int t = gpio_pin / 10;

    switch (t) {
        case 0: return gpio_fsel0;
        case 1: return gpio_fsel1;
        case 2: return gpio_fsel2;
        case 3: return gpio_fsel3;
        default: return 0;
    }
}

void gpio_set_output(int gpio_pin) {
    if(gpio_pin > 26) // rpi 3b gpio count
        return;

    uint *pin_fsel = (uint *)get_fsel_addr(gpio_pin);

    int o = gpio_pin % 10;

    int outputBit;
    switch (o) {
        case 0: outputBit = f0; break;
        case 1: outputBit = f1; break;
        case 2: outputBit = f2; break;
        case 3: outputBit = f3; break;
        case 4: outputBit = f4; break;
        case 5: outputBit = f5; break;
        case 6: outputBit = f6; break;
        case 7: outputBit = f7; break;
        case 8: outputBit = f8; break;
        case 9: outputBit = f9; break;
        default: return;
    }

    *pin_fsel |= outputBit;
    return;
}

// set GPIO <gpio_pin> on
void gpio_set_on(int gpio_pin) {
    if(gpio_pin >= 32)
        return;

    uint *set = (uint *)gpio_set0;
    *set |= (0x1 << gpio_pin);
}

// set GPIO <gpio_pin> off
void gpio_set_off(int gpio_pin) {
    if(gpio_pin >= 32)
        return;

    uint *clr = (uint *)gpio_clr0;
    *clr |= (0x1 << gpio_pin);
}

void delay(int count) {
    while (count-- > 0) {
        asm volatile("nop");
    }
}