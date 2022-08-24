#ifndef WINDOW_H
#define WINDOW_H

void init_screen8(char *vram, int x, int y);
void PUTCHINESE0(unsigned char *vram, int x, int y, char color, unsigned short CH, int xsize);
void init_mouse_cursor8(char *mouse, char bc);
void Sputs(unsigned char *vram, char *str, int x, int y, int col, int xsize);
void PowerMakeWindow(unsigned char *vram, int xsize, int ysize);
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);
void SDraw_Px(unsigned char *vram, int x, int y, int color, int xsize);
void SDraw_Box(unsigned char *vram, int x, int y, int x1, int y1, int color, int xsize);
void SDraw_Char(unsigned char *vram1, int x, int y, char c, int color, int xsize);
int sc2a(int sc);
void Draw_Cur(unsigned char *vram, int x, int y, int xsize);
void make_window8(unsigned char *buf, int xsize, int ysize, char *title);

#endif