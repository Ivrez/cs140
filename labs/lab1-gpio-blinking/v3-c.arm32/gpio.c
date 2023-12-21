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

void gpio_set_output(uint32_t gpio_pin) {
    if(gpio_pin > GPIO_CNT)
        return;

    int t = gpio_pin / 10;
    int u = gpio_pin % 10;

    uint32_t pin_fsel;

    switch (t) {
        case 0: pin_fsel = gpio_fsel0; break;
        case 1: pin_fsel = gpio_fsel1; break;
        case 2: pin_fsel = gpio_fsel2; break;
        case 3: pin_fsel = gpio_fsel3; break;
        default: return;
    }

    uint32_t current_fsel_mask = GET32(pin_fsel);

    // 001 << (unit * 3)
    // activate pin as output
    current_fsel_mask |= (GPIO_FUNC_OUTPUT << (u*FSEL_BIT_SHIFT));

    PUT32(pin_fsel, current_fsel_mask);
    return;
}

void gpio_set_input(uint32_t gpio_pin) {
    if(gpio_pin > GPIO_CNT)
        return;

    int t = gpio_pin / 10;
    int u = gpio_pin % 10;

    uint32_t pin_fsel;

    switch (t) {
        case 0: pin_fsel = gpio_fsel0; break;
        case 1: pin_fsel = gpio_fsel1; break;
        case 2: pin_fsel = gpio_fsel2; break;
        case 3: pin_fsel = gpio_fsel3; break;
        default: return;
    }

    uint32_t current_fsel_mask = GET32(pin_fsel);

    // ~(111 << (unit * 3))
    // activate pin as input
    current_fsel_mask &= ~(0b111u << (u*FSEL_BIT_SHIFT));

    PUT32(pin_fsel, current_fsel_mask);
    return;
}

// set GPIO <gpio_pin> on
void gpio_set_on(uint32_t gpio_pin) {
    if(gpio_pin > GPIO_CNT)
        return;
    PUT32(gpio_set0, (0x1 << gpio_pin));
    // or
    // uint32_t *set = (uint32_t *)gpio_set0;
    // *set |= (0x1 << gpio_pin);
}

// set GPIO <gpio_pin> off
void gpio_set_off(uint32_t gpio_pin) {
    if(gpio_pin > GPIO_CNT)
        return;
    PUT32(gpio_clr0, (0x1 << gpio_pin));
    // or
    // uint32_t *clr = (uint32_t *)gpio_clr0;
    // *clr |= (0x1 << gpio_pin);
}

void delay_cycles(unsigned count) {
    while (count-- > 0) {
        nop();
    }
    return;
}