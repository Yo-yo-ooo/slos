#define CYLS    0xff0
#define LEDS    0x0ff1
#define VMODE   0x0ff2
#define SCRNX   0x0ff4
#define SCRNY   0x0ff6
#define VARM    0x0ff8

.section .text
.globl winit
.type winit,@function
winit:
    .code16
    mov $0,%ax
    mov %ax,%ds
    mov %ax,%es
    mov %ax,%ss

    mov $0x13,%al
    mov $0x00,%ah
    int $0x10

    mov $0x02,%ah
    int $0x16
    mov %al,(LEDS)
    #init window
    movb $10,(CYLS)
    movb $8,(VMODE)
    movw $320,(SCRNX)
    movw $200,(SCRNY)
    movl $0x000a0000,(VARM)

    movb $0xff,%al
    outb %al, $0x21
    nop
    out %al,$0xal
    cli
    