/* linker.ld */
ENTRY(_start)

/* comment in ld file like this */

MEMORY
{
    ram : ORIGIN = 0x8000, LENGTH = 0x1000000
}

SECTIONS
{
    .text : { *(.text*) } > ram
    .bss : { *(.bss*) } > ram
    /DISCARD/ : { *(.comment) } > ram
}