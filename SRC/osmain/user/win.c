#include <inc/sys/window.h>
#include <inc/sys/io.h>

//...这个还没做好
// void io_cli(void);
// void io_sti(void);
// void io_out8(int port, int data);
// void io_out16(int port, int data);
// void io_out32(int port, int data);
// int io_in8(int port);
// int io_in16(int port);
// int io_in32(int port);
// int io_load_eflags(void);
// void io_store_eflags(int eflags);
// void sleep(int time);
// void io_hlt(void);

// #define COL8_000000 0
// #define COL8_FF0000 1
// #define COL8_00FF00 2
// #define COL8_FFFF00 3
// #define COL8_0000FF 4
// #define COL8_FF00FF 5
// #define COL8_00FFFF 6
// #define COL8_FFFFFF 7
// #define COL8_C6C6C6 8
// #define COL8_840000 9
// #define COL8_008400 10
// #define COL8_848400 11
// #define COL8_000084 12
// #define COL8_840084 13
// #define COL8_008484 14
// #define COL8_848484 15

// void set_palette(int start, int end, unsigned char *rgb) {
//   int eflags = io_load_eflags(); // 记录标志

//   io_cli(); // 禁止中断

//   io_out8(0x03c8, start);
//   for (int i = start; i <= end; i++) {
//     io_out8(0x03c9, rgb[0] / 4);
//     io_out8(0x03c9, rgb[1] / 4);
//     io_out8(0x03c9, rgb[2] / 4);
//     rgb += 3;
//   }

//   io_store_eflags(eflags);

//   return;
// }

// void init_palette(void) {
//   static unsigned char table_rgb[16 * 3] = {
//       0x00, 0x00, 0x00, // 黑色
//       0xff, 0x00, 0x00, // 亮红色
//       0x00, 0xff, 0x00, // 亮绿色
//       0xff, 0xff, 0x00, // 亮黄色
//       0x00, 0x00, 0xff, // 亮蓝色
//       0xff, 0x00, 0xff, // 亮紫色
//       0x00, 0xff, 0xff, // 浅亮蓝色
//       0xff, 0xff, 0xff, // 白色
//       0xc6, 0xc6, 0xc6, // 亮灰色
//       0x84, 0x00, 0x00, // 暗红色
//       0x00, 0x84, 0x00, // 暗绿色
//       0x84, 0x84, 0x00, // 暗黄色
//       0x00, 0x00, 0x84, // 暗蓝色
//       0x84, 0x00, 0x84, // 暗紫色
//       0x00, 0x84, 0x84, // 浅暗蓝色
//       0x84, 0x84, 0x84  // 暗灰色
//   };

//   set_palette(0, 15, table_rgb);

//   return;
// }

void
umain(int argc, char **argv){
    unsigned char *vram = (unsigned char *)0xa0000;
    int xSize = 320, ySize = 200;

    /* init_palette();

    boxfill8(vram, xSize, COL8_008484, 0, 0, xSize - 1, ySize - 29);
    boxfill8(vram, xSize, COL8_C6C6C6, 0, ySize - 28, xSize - 1, ySize - 28);
    boxfill8(vram, xSize, COL8_FFFFFF, 0, ySize - 27, xSize - 1, ySize - 27);
    boxfill8(vram, xSize, COL8_C6C6C6, 0, ySize - 26, xSize - 1, ySize - 1);

    boxfill8(vram, xSize, COL8_FFFFFF, 3, ySize - 24, 59, ySize - 24);
    boxfill8(vram, xSize, COL8_FFFFFF, 2, ySize - 24, 2, ySize - 4);
    boxfill8(vram, xSize, COL8_848484, 3, ySize - 4, 59, ySize - 4);
    boxfill8(vram, xSize, COL8_848484, 59, ySize - 23, 59, ySize - 5);
    boxfill8(vram, xSize, COL8_000000, 2, ySize - 4, 59, ySize - 3);
    boxfill8(vram, xSize, COL8_000000, 60, ySize - 24, 60, ySize - 3);

    boxfill8(vram, xSize, COL8_848484, xSize - 47, ySize - 24, xSize - 4,
                ySize - 24);
    boxfill8(vram, xSize, COL8_848484, xSize - 47, ySize - 23, xSize - 47,
                ySize - 4);
    boxfill8(vram, xSize, COL8_FFFFFF, xSize - 47, ySize - 3, xSize - 4,
                ySize - 3);
    boxfill8(vram, xSize, COL8_FFFFFF, xSize - 3, ySize - 24, xSize - 3,
                ySize - 3);
    for (;;) {
        io_hlt();
    } */

}