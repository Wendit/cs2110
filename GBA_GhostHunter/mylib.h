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
#define REG_DISPCNT  (*(u16 *) 0x4000000)
#define BG2_ENABLE  (1<<10)
#define MODE3 3

//Pixels
#define ROWS 160
#define COLS 240
#define OFFSET(r, c, length) ((r) * (length) + (c))
#define PIXEL_AT(r,c) (*((videoBuffer) +(OFFSET((r),(c),240))))
 extern u16* videoBuffer;

//colors
#define RGB(r,g,b)((r) | ((g) << 5) | ((b) << 10))
#define BG_COLOR (WHITE)
#define WHITE (RGB(31,31,31))
#define BLACK (RGB(0,0,0))
#define GREEN (RGB(0,31,0))
#define BLUE (RGB(0,0,31))
#define RED (RGB(31,0,0))
#define YELLOW (RGB(31,15,0))

//timer
#define REG_VCOUNT *(volatile u16*)0x04000006
#define TIMER1 60
#define TIMER2 30
#define TIMER3 10
#define TIMER4 5

//Buttons

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

//Characters
extern const unsigned char fontdata_6x8[12288];

/* DMA */

#define REG_DMA0SAD         *(const volatile u32*)0x40000B0 // source address
#define REG_DMA0DAD         *(volatile u32*)0x40000B4       // destination address
#define REG_DMA0CNT         *(volatile u32*)0x40000B8       // control register

// DMA channel 1 register definitions
#define REG_DMA1SAD         *(const volatile u32*)0x40000BC // source address
#define REG_DMA1DAD         *(volatile u32*)0x40000C0       // destination address
#define REG_DMA1CNT         *(volatile u32*)0x40000C4       // control register

// DMA channel 2 register definitions
#define REG_DMA2SAD         *(const volatile u32*)0x40000C8 // source address
#define REG_DMA2DAD         *(volatile u32*)0x40000CC       // destination address
#define REG_DMA2CNT         *(volatile u32*)0x40000D0       // control register

// DMA channel 3 register definitions
#define REG_DMA3SAD         *(const volatile u32*)0x40000D4 // source address
#define REG_DMA3DAD         *(volatile u32*)0x40000D8       // destination address
#define REG_DMA3CNT         *(volatile u32*)0x40000DC       // control register

typedef struct
{
	const volatile void *src;
	const volatile void *dst;
	unsigned int cnt;
} DMA_CONTROLLER;

#define DMA ((volatile DMA_CONTROLLER *) 0x040000B0)

// Defines
#define DMA_CHANNEL_0 0
#define DMA_CHANNEL_1 1
#define DMA_CHANNEL_2 2
#define DMA_CHANNEL_3 3

#define DMA_DESTINATION_INCREMENT (0 << 21)
#define DMA_DESTINATION_DECREMENT (1 << 21)
#define DMA_DESTINATION_FIXED (2 << 21)
#define DMA_DESTINATION_RESET (3 << 21)

#define DMA_SOURCE_INCREMENT (0 << 23)
#define DMA_SOURCE_DECREMENT (1 << 23)
#define DMA_SOURCE_FIXED (2 << 23)

#define DMA_REPEAT (1 << 25)

#define DMA_16 (0 << 26)
#define DMA_32 (1 << 26)

#define DMA_NOW (0 << 28)
#define DMA_AT_VBLANK (1 << 28)
#define DMA_AT_HBLANK (2 << 28)
#define DMA_AT_REFRESH (3 << 28)

#define DMA_IRQ (1 << 30)
#define DMA_ON (1 << 31)

//Game info
int score;
int difficulty;

//circles
typedef struct {
	int r;
	int c;
	int radius;
	u16 color;
	int dr;
	int dc;
} Circle;

typedef struct {
	Circle circle;
	int cooldown;
}Aim;

typedef struct {
	int r;
	int c;
	int dr;
	int dc;
	u8 hp;
}Enemy;

typedef struct
{
	int r;
	int c;
	int maxRange;
	int dRange;
	int offRange;
	u8 active;
} BoostItem;

#define ENEMYSIZE 20
typedef struct 
{
	Enemy enemies[6];
	int size;
} EnemyList;

typedef struct
{
	u8 frame;
	int r;
	int c;
} Bam;

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

void randomizeCircle(Circle *circle);

void drawChar(int row, int col, char ch, unsigned short color);

void drawString(int row, int col, char *str, unsigned short color);

void drawCharWSize(int row, int col, char ch, unsigned short color, u16 size);

void drawStringWSize(int row, int col, char *str, unsigned short color, u16 size);

void drawHollowCircleWStruct(Circle *circle, u16 color);

void toString(char *str, int num);

void drawImage3(int row, int col, int height, int width, const unsigned short* color);

void drawAim(Aim *aim, u16 color);

void drawBGDMA(const unsigned short* color);

void drawPartialBGDMA(int row, int col, int height, int width, const unsigned short* color);

void randomizeEnemy(Enemy *enemy);

void drawEnemy(EnemyList *enemyList, const unsigned short* color1,const unsigned short* color2,const unsigned short* color3,const unsigned short* color4);

void updateEnemy(EnemyList *enemyList, int *timeLeft);

u8 checkCollision(Enemy *enemy, Aim *aim);

void shoot(EnemyList *enemyList, Aim *aim, Bam *bam, BoostItem *boostItem , int *score, int *timeLeft, int *factor, int *feverTime);

void drawBam(Bam *bam, const unsigned short *color);

void moreEnemy(EnemyList *enemyList);

void generateBoostItem(BoostItem *boostItem);

void updateBoostItem(BoostItem *boostItem);

void drawBoostItem(BoostItem *boostItem, const unsigned short *color);

u8 checkBoostItem(BoostItem *boostItem, Aim *aim);

#endif
