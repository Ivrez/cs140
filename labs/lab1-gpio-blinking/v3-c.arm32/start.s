/* start.s */
.section .text.bootload
.globl _start

_start:
    /* set up the stack pointer */
    ldr sp, =0x8000

    /* call the main function */
    bl main

hang: b hang /* infinite loop */


// trivial routine to write a 32-bit passed as the second argument
// (register r1) to the address passed as the first argument (register r0)
// defined in rpi.h
.globl put32
.globl PUT32
put32:
PUT32:
    str r1,[r0]
    bx lr

// trivial routine to do a 32-bit load of the address passed as
// the first argument.
// defined in rpi.h
.globl get32
.globl GET32
get32:
GET32:
    ldr r0,[r0]
    bx lr

// do nothing: put the call here so the compiler cannot optimize.
// defined in rpi.h
.globl nop
nop:
    bx lr
