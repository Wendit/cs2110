/**
	File name: mylib.h
	Author: Wendi Tang
	History: v0.1 completed by WT 2014/10/21 
	Description: This file contains the macros and function
	prototypes used in the game library.
*/

#ifndef MYLIB_H
#define MYLIB_H

#include <stdlib.h>

typedef unsigned short u16;
typedef unsigned char u8;

#define TRUE 1
#define FALSE 0

//display controls
#define REG_DISPCNT  *(u16 *) 0x4000000
#define BG2_ENABLE  (1<<10)
#define MODE3 3

//Pixels
#define ROWS 160
#define COLS 240
#define OFFSET(r, c, length) ((r) * (length) + (c))
#define PIXEL_AT(r,c) (*((u16 *)0x6000000+(OFFSET((r),(c),240))))
 extern u16* videoBuffer;

//colors
#define RGB(r,g,b)((r) + ((g) << 5) + ((b) << 10))
#define BG_COLOR (WHITE)
#define WHITE (RGB(31,31,31))
#define BLACK (RGB(0,0,0))
#define GREEN (RGB(0,31,0))
#define BLUE (RGB(0,0,31))
#define RED (RGB(31,0,0))

//timer
#define REG_VCOUNT *(volatile u16*)0x04000006
#define TIMER1 60
#define TIMER2 30
#define TIMER3 10
#define TIMER4 5

// Buttons

#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)

#define BUTTONS (*(volatile unsigned int *)0x4000130)
#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)
#define KEY_DOWN_RECORDED(key)  ((keyRecorded) & key)
u16 keyRecorded;

//characters
extern const unsigned char fontdata_6x8[12288];

//Game info
int score;
int difficulty;

//string bitmap
struct StringBitmap{
	int r;
	int c;
	u16 size;
	u16 color;
	char* str;
	int dr;
	int dc;
	int width;
	int length;
};

//circles
struct Circle{
	int r;
	int c;
	int radius;
	u16 color;
	int dr;
	int dc;
};

//Me
struct Me{
	struct Circle core;
	int wallNum;
	int hp;
};

struct Boost{
	int r;
	int c;
	int active;
};

//function prototypes
void setPixel(int r, int c, u16 color);

void drawRect(int r, int c, int width, int height, u16 color);

void drawHollowRect(int r, int c, int width, int height,u16 color);

void plotLine(int x0, int y0, int x1, int y1, u16 color);

void vid_vsync();

void randomPixels();

u16 randomColor();

void drawCircle(int r0, int c0 , int radius, u16 color);

void drawHollowCircle(int r0, int c0 , int radius, u16 color);

void getKeyRecord();

void resetKeyRecord();

void randomizeCircle(struct Circle *circle);

void updateCircle(struct Circle *circle);

void drawChar(int row, int col, char ch, unsigned short color);

void drawString(int row, int col, char *str, unsigned short color);

void drawCharWSize(int row, int col, char ch, unsigned short color, u16 size);

void drawStringWSize(int row, int col, char *str, unsigned short color, u16 size);

void initializeStringBitMap(struct StringBitmap *stringBitmap,int r, int c, u16 size, u16 color, char* str, 
	int dr, int dc);
void drawHollowCircleWStruct(struct Circle *circle, u16 color);

void updateMe(struct Me *me);

void drawMe(struct Me *me, u16 color);

void initializeMe(struct Me *me);

void toString(char str[], int num);

void generateCircle(struct Circle *circle);

void updateGameCircle(struct Circle *circle);

void checkCollisionWithCircle(struct Circle *circle, struct Me *me);

void randomizeBoostItem(struct Boost *boost);

void checkCollisionWithBoostItem(struct Boost *boost, struct Me *me);

void drawBoostItem(struct  Boost *boost, u16 color);

#endif
