#include <inc/lib.h>

extern unsigned int memsize;
char *font;

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

void init_screen8(char *vram, int x, int y)
{
	memset(vram, 14, x * y);
}
void PUTCHINESE0(unsigned char *vram, int x, int y, char color, unsigned short CH, int xsize)
{
	extern char *hzkfont;
	int i, j, k, offset;
	int flag;
	unsigned char buffer[32];
	unsigned char word[2] = {CH & 0xff, (CH & 0xff00) >> 8}; // 将字符转换为两个字节
	unsigned char key[8] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
	unsigned char *p = hzkfont;
	offset = (94 * (unsigned int)(word[0] - 0xa0 - 1) + (word[1] - 0xa0 - 1)) * 32;
	p = p + offset;
	//读取，并写入到vram中
	for (i = 0; i < 32; i++)
	{
		buffer[i] = p[i];
	}
	for (k = 0; k < 16; k++)
	{
		for (j = 0; j < 2; j++)
		{
			for (i = 0; i < 8; i++)
			{
				flag = buffer[k * 2 + j] & key[i];
				if (flag)
				{
					// Draw_Px(x + i + j * 8, y + k, color);
					vram[(y + k) * xsize + (x + i + j * 8)] = color;
				}
			}
		}
	}
}
void init_mouse_cursor8(char *mouse, char bc)
/* 鼠标的数据准备（16x16） */
{
	int x, y;

	for (y = 0; y < 16; y++)
	{
		for (x = 0; x < 16; x++)
		{
			if (mouse_cur_graphic[y][x] == '*')
			{
				mouse[y * 16 + x] = 0x0;
			}
			if (mouse_cur_graphic[y][x] == 'O')
			{
				mouse[y * 16 + x] = 0xf;
			}
			if (mouse_cur_graphic[y][x] == '.')
			{
				mouse[y * 16 + x] = bc;
			}
		}
	}
	return;
}
void Sputs(unsigned char *vram, char *str, int x, int y, int col, int xsize)
{
	int i;
	for (i = 0; str[i] != 0; i++)
	{
		SDraw_Char(vram, x + i, y, str[i], col, xsize);
	}
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
void SDraw_Char(unsigned char *vram1, int x, int y, char c, int color, int xsize)
{
	extern char *ascfont;
	x *= 8;
	y *= 16;
	unsigned char *vram = (unsigned char *)vram1;
	unsigned char *p;
	unsigned char *font;
	int i, j;
	font = ascfont;
	font += c * 16;
	int char_color = color & 0x0f;
	int bg_color = (color & 0xf0) >> 4;
	for (i = 0; i < 16; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (font[i] & (0x80 >> j))
			{
				p = vram + (y + i) * xsize + x + j;
				*p = color;
			}
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
void make_window8(unsigned char *buf, int xsize, int ysize, char *title)
{
	static char closebtn[14][16] = {
		"OOOOOOOOOOOOOOO@",
		"OQQQQQQQQQQQQQ$@",
		"OQQQQQQQQQQQQQ$@",
		"OQQQ@@QQQQ@@QQ$@",
		"OQQQQ@@QQ@@QQQ$@",
		"OQQQQQ@@@@QQQQ$@",
		"OQQQQQQ@@QQQQQ$@",
		"OQQQQQ@@@@QQQQ$@",
		"OQQQQ@@QQ@@QQQ$@",
		"OQQQ@@QQQQ@@QQ$@",
		"OQQQQQQQQQQQQQ$@",
		"OQQQQQQQQQQQQQ$@",
		"O$$$$$$$$$$$$$$@",
		"@@@@@@@@@@@@@@@@"};

	int x, y;
	char c;
	boxfill8(buf, xsize, 0x7, 0, 0, xsize - 1, 0);
	boxfill8(buf, xsize, 0xf, 1, 1, xsize - 2, 1);
	boxfill8(buf, xsize, 0x7, 0, 0, 0, ysize - 1);
	boxfill8(buf, xsize, 0xf, 1, 1, 1, ysize - 2);
	boxfill8(buf, xsize, 0x8, xsize - 2, 1, xsize - 2, ysize - 2);
	boxfill8(buf, xsize, 0x0, xsize - 1, 0, xsize - 1, ysize - 1);
	boxfill8(buf, xsize, 0x7, 2, 2, xsize - 3, ysize - 3);
	boxfill8(buf, xsize, 12, 3, 3, xsize - 4, 20);
	boxfill8(buf, xsize, 0x8, 1, ysize - 2, xsize - 2, ysize - 2);
	boxfill8(buf, xsize, 0x0, 0, ysize - 1, xsize - 1, ysize - 1);
	putfonts8_asc(buf, xsize, 24, 4, 0xf, title);

	for (y = 0; y < 14; y++)
	{
		for (x = 0; x < 16; x++)
		{
			c = closebtn[y][x];
			if (c == '@')
			{
				c = 0x0;
			}
			else if (c == '$')
			{
				c = 8;
			}
			else if (c == 'Q')
			{
				c = 7;
			}
			else
			{
				c = 0xf;
			}
			buf[(5 + y) * xsize + (xsize - 21 + x)] = c;
		}
	}
	return;
}