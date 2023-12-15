#ifndef __RPI_H__
#define __RPI_H__

#include <stdint.h> // uint32_t

#define GPIO_CNT 26 // rpi 3b gpio count
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

// Used to write to device memory.  Use this instead of a raw store.
// Writes the 32-bit value <v> to address <addr>.
// Safer alternative to *(uint32_t *)addr = v;
// Like PUT32, but takes <addr> as a pointer.
void put32(volatile void *addr, uint32_t v);


// Used to write to device memory.  Use this instead of a raw store.
// Writes the 32-bit value <v> to address <addr>.
// Safer alternative to *(uint32_t *)addr = v;
// Like put32, but takes <addr> as an int.
void PUT32(uint32_t addr, uint32_t v);


// Used to read from device memory.  Use this instead of a raw dereference.
// Returns the 32-bit value at address <addr>.
// Safer alternative to *(uint32_t *)addr.
// Like GET32, but takes <addr> as a pointer.
uint32_t get32(const volatile void *addr);


// Used to read from device memory.  Use this instead of a raw dereference.
// Returns the 32-bit value at address <addr>.
// Safer alternative to *(uint32_t *)addr.
// Like get32, but takes <addr> as an int.
uint32_t GET32(uint32_t addr);


// An assembly routine that does nothing.
// The compiler cannot optimize away an external function call, so we can use
// it to prevent the compiler optimizing away loops.
void nop(void);


// counts down <ticks> cycles.
void delay_cycles(unsigned count);

void gpio_set_output(uint32_t gpio_pin);

void gpio_set_on(uint32_t gpio_pin);

void gpio_set_off(uint32_t gpio_pin);

#endif