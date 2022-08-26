#ifndef WINDOW_H
#define WINDOW_H

void init_screen8(char *vram, int x, int y);
void init_mouse_cursor8(char *mouse, char bc);
void PowerMakeWindow(unsigned char *vram, int xsize, int ysize);
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1);
void SDraw_Px(unsigned char *vram, int x, int y, int color, int xsize);
void SDraw_Box(unsigned char *vram, int x, int y, int x1, int y1, int color, int xsize);
int sc2a(int sc);
void Draw_Cur(unsigned char *vram, int x, int y, int xsize);
void clear();

#endif