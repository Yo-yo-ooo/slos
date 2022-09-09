#ifndef _FUNCTION_H
#define _FUNCTION_H

#define io_hlt()  asm("hlt")
#define io_cli()  asm("cli")
int load_cr0(void){
    asm volatile(
        "mov %eax,%cr0"
        );
}
void store_cr0(int cr0){
    asm(
        "mov %eax,%0"
        "mov %cr0,%eax"
    :"=a"(cr0));
}
#define io_sti()  asm("sti")
void io_stihlt(void){
     asm(
        "sti\n\t"
        "hlt"
    );
}
int io_in8(int port){
    asm(
        "mov %edx,%0"
        "mov %eax,0"
        "in %al,%dx"
        :"=d"(port)
    );
}
int io_in16(int port){
    asm(
        "mov %edx,%0"
        "mov %eax,0"
        "int %ax,%dx"
        :"=d"(port)
    );
}
int io_in32(int port){
    asm(
        "mov %edx,%0"
        "int %eax,%dx"
        :"=d"(port)
    );
}
void io_out8(int port, int data){
    asm(
        "mov %edx,%0"
        "mov %al,%1"
        "out %dx,%al"
        :"=d"(port),"=a"(data)
    );
}
void io_out16(int port, int data){
    asm(
        "mov %edx,%0"
        "mov %eax,%1"
        "out %dx,%ax"
        :"=d"(port),"=a"(data)
    );
}
void io_out32(int port, int data){
    asm(
        "mov %edx,%0"
        "mov %eax,%1"
        "out %dx,%eax"
        :"=d"(port),"=a"(data)
    );
}

void Clear_Screen(void){

}
#define write_mem8(addr,data8)   (*(volatile char *)(addr))=(char)data8

#endif