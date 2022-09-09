#include <inc/lib.h>
#include <inc/sys/window.h>
#include <inc/function.h>

#define CYLS			0x0ff0
#define LEDS			0x0ff1
#define VMODE			0x0ff2
#define SCRNX			0x0ff4
#define SCRNY			0x0ff6
#define VRAM			0x0ff8

extern unsigned int memsize;
char *font;
unsigned char table_rgb[16 * 3] = {
    0x00, 0x00, 0x00,
    0xff, 0x00, 0x00,
    0x00, 0xff, 0x00,
    0xff, 0xff, 0x00,
    0x00, 0x00, 0xff,
    0xff, 0x00, 0xff,
    0x00, 0xff, 0xff,
    0xc6, 0xc6, 0xc6,
    0x84, 0x84, 0x84,
    0x84, 0x00, 0x00,
    0x00, 0x84, 0x00,
    0x84, 0x84, 0x00,
    0x00, 0x00, 0x84,
    0x84, 0x00, 0x84,
    0x00, 0x84, 0x84,
    0xFF, 0xFF, 0xFF
};
char keytable[0x54] = {
	0, 0, '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', '\b', '\t',
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', 10, 0, 'A', 'S',
	'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '\"', '~', 0, '|', 'Z', 'X', 'C', 'V',
	'B', 'N', 'M', '<', '>', '?', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, '7', 'D', '8', '-', '4', '5', '6', '+', '1',
	'2', '3', '0', '.'};
char keytable1[0x54] = {
	0, 0, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b', '\t',
	'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 10, 0, 'a', 's',
	'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0, '\\', 'z', 'x', 'c', 'v',
	'b', 'n', 'm', ',', '.', '/', 0, '*', 0, ' ', 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, '7', '8', '9', '-', '4', '5', '6', '+', '1',
	'2', '3', '0', '.'};
char mouse_cur_graphic[16][16] = {
	"*...............",
	"**..............",
	"*O*.............",
	"*OO*............",
	"*OOO*...........",
	"*OOOO*..........",
	"*OOOOO*.........",
	"*OOOOOO*........",
	"*OOOOOOO*.......",
	"*OOOO*****......",
	"*OO*O*..........",
	"*O*.*O*.........",
	"**..*O*.........",
	"*....*O*........",
	".....*O*........",
	"......*........."};
int caps_lock = 0, shift = 0;
void init_screen8(char *vram, int x, int y)
{
	memset(vram, 14, x * y);
}
void PowerMakeWindow(unsigned char *vram, int xsize, int ysize)
{
	// 160*52
	for (int i = 0; i < ysize; i++)
	{
		for (int j = 0; j < xsize; j++)
		{
			vram[i * xsize + j] = 0xf;
		}
	}
}
void boxfill8(unsigned char *vram, int xsize, unsigned char c, int x0, int y0, int x1, int y1)
{
	int x, y;
	for (y = y0; y <= y1; y++)
	{
		for (x = x0; x <= x1; x++)
			vram[y * xsize + x] = c;
	}
	return;
}

void SDraw_Px(unsigned char *vram, int x, int y, int color, int xsize)
{
	unsigned char *p;
	p = vram + (y * xsize + x);
	*p = color;
	return;
}
void SDraw_Box(unsigned char *vram, int x, int y, int x1, int y1, int color, int xsize)
{
	int i, j;
	for (i = x; i <= x1; i++)
	{
		for (j = y; j <= y1; j++)
		{
			SDraw_Px(vram, i, j, color, xsize);
		}
	}
	return;
}
int sc2a(int sc)
{
	int ch = sc;
	if (keytable[ch] == 0x00)
	{
		return 0;
	}
	if (ch == 0x48 || ch == 0x50 || ch == 0x4b || ch == 0x4d) //  Ƿ         ַ
	{
		if (ch == 0x48)
		{
			return -1;
		}
		else if (ch == 0x50)
		{
			return -2;
		}
		else if (ch == 0x4b)
		{
			return -3;
		}
		else if (ch == 0x4d)
		{
			return -4;
		}
	}
	else if (shift == 0 && caps_lock == 0)
	{
		return keytable1[ch];
	}
	else if (shift == 1 || caps_lock == 1)
	{
		return keytable[ch];
	}
	else if (shift == 1 && caps_lock == 1)
	{
		return keytable1[ch];
	}
}
int first1 = 0;
void Draw_Cur(unsigned char *vram, int x, int y, int xsize)
{
	static char CUR[16][8] = {
		"........",
		"........",
		"........",
		"........",
		"........",
		"........",
		"........",
		"........",
		"........",
		"........",
		"........",
		"........",
		"........",
		"........",
		"********",
		"********"};
	int i, j;
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (CUR[i][j] == '.')
			{
				vram[(y + i) * xsize + x + j] = 99;
			}
			else if (CUR[i][j] == '*')
			{
				vram[(y + i) * xsize + x + j] = 0xf;
			}
		}
	}
}

void Move_Cursor(short x, short y)
{

	int res = y * 80 + x;
	ASM_call(res);
}

void clear(){
	int i,j;
	for(i = 0; i < 160;i+=2){
		for(j = 0; i < 25; j++){
			*(char *)(0xb8000 + j * 160 + i) = ' ';
			*(char *)(0xb8000 + j * 160 + i + 1) = 0xFF;
		}
	}
	Move_Cursor(0,0);
}

void set_palette(int start, int end, unsigned char *rgb){
	int i, eflags;
	eflags = io_load_eflags();
	io_cli();
	io_out8(0x03c8, start);
	for(i = start; i <= end; i++){
		io_out8(0x03c9,rgb[0] / 4);
		io_out8(0x03c9,rgb[1] / 4);
		io_out8(0x03c9,rgb[2] / 4);
	}
	io_store_eflags(eflags);
	return;
}

void init_palette(void){
	set_palette(0, 15, table_rgb);
	return;
}

