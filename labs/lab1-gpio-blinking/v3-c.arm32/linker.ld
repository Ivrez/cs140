/* linker.ld */
ENTRY(_start)

/* comment in ld file like this */

SECTIONS {
    . = 0x8000; /* start address */

    .text : {
        *(.text.startup)
        *(.text)
    }

    .data : { /* .data refers to initialized global and static objects */
        *(.data)
    }

    .bss : { /* .bss refers to uninitialized global and static objects */
        *(.bss)
    }

    /DISCARD/ : {
        *(.comment)
    }
}
