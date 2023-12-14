/* main.c */

typedef unsigned int uint;

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
    if(gpio_pin > 26) // rpi 3b gpio count
        return 0;

    int t = gpio_pin / 10;

    uint fsel;
    switch (t) {
        case 0:
            fsel = gpio_fsel0;
            break;
        case 1:
            fsel = gpio_fsel1;
            break;
        case 2:
            fsel = gpio_fsel2;
            break;
        case 3:
            fsel = gpio_fsel3;
            break;
    }
    return fsel;
}

void gpio_set_output(int gpio_pin) {
    if(gpio_pin > 26) // rpi 3b gpio count
        return;

    uint *pin_fsel = (uint *)get_fsel_addr(gpio_pin);

    int o = gpio_pin % 10;

    int bitOutputPosition;
    switch (o) {
        case 0:
            bitOutputPosition = f0;
            break;
        case 1:
            bitOutputPosition = f1;
            break;
        case 2:
            bitOutputPosition = f2;
            break;
        case 3:
            bitOutputPosition = f3;
            break;
        case 4:
            bitOutputPosition = f4;
            break;
        case 5:
            bitOutputPosition = f5;
            break;
        case 6:
            bitOutputPosition = f6;
            break;
        case 7:
            bitOutputPosition = f7;
            break;
        case 8:
            bitOutputPosition = f8;
            break;
        case 9:
            bitOutputPosition = f9;
            break;
    }

    *pin_fsel |= bitOutputPosition;
    return;
}

void delay(int count) {
    while (count-- > 0) {
        asm volatile("nop");
    }
}

int main(void) {
    int led1 = 21;
    int led2 = 20;

    gpio_set_output(led1);
    gpio_set_output(led2);
    
    uint *set = (uint *)gpio_set0;
    uint *clr = (uint *)gpio_clr0;

    while (1) {
        *set |= (0x1 << led1);
        *set |= (0x1 << led2);

        delay(50000);

        *clr |= (0x1 << led1);
        *clr |= (0x1 << led2);

        delay(50000);
    }
}
