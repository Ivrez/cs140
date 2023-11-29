#define GPIO_BASE (0x3F000000 + 0x200000)

// Read BCM2835-ARM-Peripherals to understand the magic
#define GPFSEL1_FSEL_16 (0b001 << 18)
#define GPFSEL2_FSEL_20 (0b001 << 0)

volatile unsigned *GPFSEL1 = (volatile unsigned *)(GPIO_BASE + 0x04);
volatile unsigned *GPFSEL2 = (volatile unsigned *)(GPIO_BASE + 0x08);
volatile unsigned *GPSET0  = (volatile unsigned *)(GPIO_BASE + 0x1C);
volatile unsigned *GPCLR0  = (volatile unsigned *)(GPIO_BASE + 0x28);


static void sleep_seconds(float sec) {
  for (unsigned int i = 0; i < sec * 1000.0f * 1000.0f * 6; i++) {
      asm volatile("nop");
  }
}

int main(void) {

  // Set GPIO Pins 16 and as output.
  *GPFSEL1 = GPFSEL1_FSEL_16;
  *GPFSEL2 = GPFSEL2_FSEL_20;

  // Continuously set and clear GPIO 16, 20.
  while (1) {
    *GPSET0 = 1 << 16;
    *GPSET0 = 1 << 20;
    sleep_seconds(0.02);
    *GPCLR0 = 1 << 16;
    *GPCLR0 = 1 << 20;
    sleep_seconds(0.03);


    *GPSET0 = 1 << 16;
    *GPSET0 = 1 << 20;
    sleep_seconds(0.05);
    *GPCLR0 = 1 << 16;
    *GPCLR0 = 1 << 20;
    sleep_seconds(0.03);
  }
}