/* start.s */
.section .text.startup
.globl _start

_start:
    /* Set up the stack pointer */
    ldr sp, =0x8000

    /* Call the main function */
    bl main

    /* Halt the system */
    b .

/* Define a dummy IRQ handler to prevent undefined reference */
.section .text
.globl __dummy_irq_handler
__dummy_irq_handler:
    b __dummy_irq_handler
