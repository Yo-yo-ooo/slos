#ifndef _NASMFUC_H
#define _NASMFUC_H

#ifdef __cplusplus
extern "C" {
#endif
void _io_cli(void);
void _io_sti(void);
void _io_out8(int port, int data);
void _io_out16(int port, int data);
void _io_out32(int port, int data);
int _io_in8(int port);
int _io_in16(int port);
int _io_in32(int port);
int _io_load_eflags(void);
void _io_store_eflags(int eflags);

#ifdef __cplusplus
}
#endif

#endif