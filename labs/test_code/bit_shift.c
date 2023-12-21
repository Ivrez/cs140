#include <stdio.h>
#include <stdint.h> // uint32_t

#define FSEL_BIT_SHIFT 3 // FSEL0(2-0) FSEL1(5-3) FSEL2(8-6)

typedef enum {
    GPIO_FUNC_INPUT   = 0,
    GPIO_FUNC_OUTPUT  = 1,
    GPIO_FUNC_ALT0    = 4,
    GPIO_FUNC_ALT1    = 5,
    GPIO_FUNC_ALT2    = 6,
    GPIO_FUNC_ALT3    = 7,
    GPIO_FUNC_ALT4    = 3,
    GPIO_FUNC_ALT5    = 2,
} gpio_func_t;

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

void main() {
    uint32_t pin_fsel;
    uint32_t current_fsel_mask = 0x3fffffff;
    //uint32_t current_fsel_mask = 0x06a4e412;
    //uint32_t current_fsel_mask = 0x0;
    uint32_t new_input_mask = 0;

    printf("start fsel mask 0x%x\n",current_fsel_mask);
    for(int gpio_pin=9; gpio_pin>0; gpio_pin--){

        int t = gpio_pin / 10;
        int u = gpio_pin % 10;

        switch (t) {
            case 0: pin_fsel = gpio_fsel0; break;
            case 1: pin_fsel = gpio_fsel1; break;
            case 2: pin_fsel = gpio_fsel2; break;
            case 3: pin_fsel = gpio_fsel3; break;
            default: return;
        }

        // 001 << (unit * 3) 
        // activate pin as output
        //current_fsel_mask |= (GPIO_FUNC_OUTPUT << (u * FSEL_BIT_SHIFT));

        // ~(111 << (unit * 3))
        // activate pin as input
        current_fsel_mask &= ~(0b111u << (u * FSEL_BIT_SHIFT));

        printf("pin: %d shift: %d current mask: 0x%x\n", gpio_pin, u * FSEL_BIT_SHIFT, current_fsel_mask);
    }
    return;
}