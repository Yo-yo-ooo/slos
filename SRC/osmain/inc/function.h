#ifndef _FUNCTION_H
#define _FUNCTION_H

#define io_hlt()  asm("hlt")
#define io_cli()  asm("cli")
int load_cr0(void);
void store_cr0(int cr0);
#define io_sti()  asm("sti")
void io_stihlt(void);
int io_in8(int port);
int io_in16(int port);
int io_in32(int port);
void io_out8(int port, int data);
void io_out16(int port, int data);
void io_out32(int port, int data);

void Clear_Screen(void);
#define write_mem8(addr,data8)   (*(volatile char *)(addr))=(char)data8

#endif