#define GPIO_BASE (0x3F000000 + 0x200000)

// Read BCM2835-ARM-Peripherals to understand the magic
#define GPFSEL1_FSEL_16 (0b001 << 18)
#define GPFSEL2_FSEL_20 (0b001 << 0)

typedef unsigned int uint;

uint *GPFSEL1 = (uint *)(GPIO_BASE + 0x04);
uint *GPFSEL2 = (uint *)(GPIO_BASE + 0x08);
uint *GPSET0  = (uint *)(GPIO_BASE + 0x1C);
uint *GPCLR0  = (uint *)(GPIO_BASE + 0x28);


void main(void)
{
  // Set GPIO Pins 16 and as output.
  *GPFSEL1 = GPFSEL1_FSEL_16;
  *GPFSEL2 = GPFSEL2_FSEL_20;

  // Continuously set and clear GPIO 16, 20.
  while (1) {
    *GPSET0 = 1 << 16;
    *GPSET0 = 1 << 20;
    *GPCLR0 = 1 << 16;
    *GPCLR0 = 1 << 20;
  }
}
