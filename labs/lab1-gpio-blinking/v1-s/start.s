// ARM32 code (Armv7-A)

// for understanding:
// BCM2837 ARM Peripherals
// and https://tomeko.net/online_tools/bin_to_32bit_hex.php

.global _start

.equ GPIO_BASE, 0x3F000000 + 0x200000

.equ GPFSEL1, 0x04 // GPIO Function Select 1 offset
.equ GPFSEL2, 0x08 // GPIO Function Select 2 offset

.equ GPFSET0, 0x1c
.equ GPFCLR0, 0x28

.equ GPIO_21_OUTPUT, 0x00000008
.equ GPIO_20_OUTPUT, 0x00000001
.equ GPIO_16_OUTPUT, 0x00040000

.equ GPIO_21_VAL, 0x200000 // 21 in hex
.equ GPIO_20_VAL, 0x100000 // 20 in hex
.equ GPIO_16_VAL, 0x10000  // 16 in hex

_start:
	ldr r0, =GPIO_BASE
	ldr r1, =GPIO_16_OUTPUT
	ldr r2, =GPIO_20_OUTPUT

	str r1, [r0, #GPFSEL1]
	str r2, [r0, #GPFSEL2]

	# set counter
	ldr r3, =0x80000

loop:
	# turn on the LED
	ldr r1, =GPIO_20_VAL // value of GPIO_16 to write to set register
	ldr r2, =GPIO_16_VAL // value of GPIO_20 to write to set register
	str r1, [r0, #GPFSET0] // store in set register
	str r2, [r0, #GPFSET0] // store in set register

	# wait for some time, delay
	eor r10, r10, r10 // way of seting 0 to register
	delay1:
		add r10, r10, #1 // add 1 to r10
		cmp r10, r3 // if r10 not equal to r3(0x80000)
		bne delay1

	# turn off the LED
	ldr r1, =GPIO_20_VAL // value of GPIO_16 to write to set register
	ldr r2, =GPIO_16_VAL // value of GPIO_20 to write to set register
	str r1, [r0, #GPFCLR0] // store in set register
	str r2, [r0, #GPFCLR0] // store in set register

	# wait for some time, delay
	eor r10, r10, r10
	delay2:
		add r10, r10, #1
		cmp r10, r3
		bne delay2

	b loop
