typedef unsigned int uint;

enum rpiRegisters {
    GPIO_BASE = 0x3f000000 + 0x200000,
    gpio_fsel0 = (GPIO_BASE + 0x00),
    gpio_fsel1 = (GPIO_BASE + 0x04),
    gpio_fsel2 = (GPIO_BASE + 0x08),
    gpio_set0  = (GPIO_BASE + 0x1C),
    gpio_clr0  = (GPIO_BASE + 0x28),
    gpio_lev0  = (GPIO_BASE + 0x34),
};

enum fselOutputOffset {
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


void gpio_set_on(uint pin) {
    if(pin >= 32)
        return;
}

void gpio_set_off(uint pin) {
    if(pin >= 32)
        return;
  // implement this
  // use <gpio_clr0>
}


void gpio_set_output(uint pin) {
    if(pin > 26) // pi 3b gpio count
        return;

    uint t, o;
    t = pin / 10;
    o = pin % 10;

    uint* registerAddress;

    switch (t) {
        case 0:
            put32(registerAddress, gpio_fsel0);
            break;
        case 1:
            put32(registerAddress, gpio_fsel1);
            break;
        case 2:
            put32(registerAddress, gpio_fsel2);
            break;
    }

    unsigned bitOffset;
    switch (o) {
        case 0:
            bitOffset = f0;
            break;
        case 1:
            bitOffset = f1;
            break;
        case 2:
            bitOffset = f2;
            break;
        case 3:
            bitOffset = f3;
            break;
        case 4:
            bitOffset = f4;
            break;
        case 5:
            bitOffset = f5;
            break;
        case 6:
            bitOffset = f6;
            break;
        case 7:
            bitOffset = f7;
            break;
        case 8:
            bitOffset = f8;
            break;
        case 9:
            bitOffset = f9;
            break;
    }

	*registerAddress |= (0b001 << bitOffset);
	return;
}

void main(void){
	gpio_set_output(20);

    uint* registerAddress;

	int i = 0;
	while(1)
	{
		put32(gpio_set0, 1<<20);

		//delay
		i = 0;
		while (i < 0x800000)
		{
			i++;
		}

		//turn off pin 21
		put32(gpio_clr0, 1<<20);

		//delay
		i = 0;
		while (i < 0x800000)
		{
			i++;
		}
	}
}