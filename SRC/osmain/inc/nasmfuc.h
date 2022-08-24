#ifndef _NASMFUC_H
#define _NASMFUC_H

#ifdef __cplusplus
extern "C" {
#endif
void io_cli(void);
void io_sti(void);
void io_out8(int port, int data);
void io_out16(int port, int data);
void io_out32(int port, int data);
int io_in8(int port);
int io_in16(int port);
int io_in32(int port);
int io_load_eflags(void);
void io_store_eflags(int eflags);
void sleep(int time);
void io_hlt(void);

#ifdef __cplusplus
}
#endif

#endif