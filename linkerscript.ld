
ENTRY(start)
SECTIONS{
    . = 0x00100000;
    .text : {
        code = .;
        *(.text)
        *(.rodata)

    }
    .data : {
        *(.data)
        . = ALIGN(4096);
    }
    .bss :{
        bss = .;
        *(.bss)
    }
    end = .;
}
