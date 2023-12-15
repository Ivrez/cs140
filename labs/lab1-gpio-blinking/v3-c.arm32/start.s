/* start.s */
.section .text.bootload
.globl _start

_start:
    /* set up the stack pointer */
    ldr sp, =0x8000

    /* call the main function */
    bl main

hang: b hang /* infinite loop */