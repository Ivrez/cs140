/* linker.ld */
ENTRY(_start)

/* comment in ld file like this */

MEMORY
{
    ram : ORIGIN = 0x8000, LENGTH = 0x1000000
}

SECTIONS
{
    .text.bootload : { *(.text.bootload) } > ram /* start.s */
    .text : { *(.text) } > ram /* c code */
    .data : { *(.data) } > ram /* .data refers to initialized global and static objects */
    .bss : { *(.bss) } > ram /* .bss refers to uninitialized global and static objects */
    /DISCARD/ : { *(.comment) } > ram /* exclude code comments */
}