ENTRY(_start)

SECTIONS
{
    . = 0x8000;         /* Set the current address to 0x8000. */
    __start = .;        /* Define the symbol __start with the current address. */

    .text : {           /* Define the .text section for executable code. */
        KEEP(*(.text.boot)) /* Keep all objects in .text.boot section. */
        *(.text)        /* Include all other objects in the .text section. */
    }

    . = ALIGN(4096);    /* Align the current address to a 4096-byte boundary. */

    .rodata : {         /* Define the .rodata section for read-only data. */
        *(.rodata)      /* Include all objects in the .rodata section. */
    }

    . = ALIGN(4096);    /* Align the current address to a 4096-byte boundary. */

    .data : {           /* Define the .data section for initialized data. */
        *(.data)        /* Include all objects in the .data section. */
    }

    . = ALIGN(4096);    /* Align the current address to a 4096-byte boundary. */

    __bss_start = .;    /* Define the symbol __bss_start with the current address. */

    .bss : {            /* Define the .bss section for uninitialized data. */
        bss = .;        /* Define the symbol 'bss' with the current address. */
        *(.bss)         /* Include all objects in the .bss section. */
    }

    . = ALIGN(4096);    /* Align the current address to a 4096-byte boundary. */

    __bss_end = .;      /* Define the symbol __bss_end with the current address. */
    __bss_size = __bss_end - __bss_start; /* Calculate the size of the .bss section. */

    __end = .;          /* Define the symbol __end with the current address. */
}