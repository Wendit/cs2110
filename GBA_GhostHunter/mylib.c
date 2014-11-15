/**
	File name: mylib.c
	Author: Wendi Tang
	History: v0.1 completed by WT 2014/10/21 
	Description: This file is the game library. It contains 
	the function implementations.
*/
#include "mylib.h"

u16* videoBuffer = 	(u16 *)0x6000000;

/**
	Description: Set the specific pixel to the given color
	
	Parameters: int r - the row of the pixel
				int c - the column of the piexel 
				u16 color - the color of the pixel
	Return: None
*/
void setPixel(int r, int c, u16 color)
{
	(PIXEL_AT(r,c)) = color;

	}

/**
	Description: Draw a hollow rectangle
	
	Parameters: int r - the row of the pixel at the upper 
				left corner of the rectangle
				int c - the column of the piexel at the upper
				left coner of the rectangle 
				int width - the width of the rectangle
				int height - the height of the rectangle
				u16 color - the color of the rectangle
	Return: None
*/
void drawHollowRect(int r, int c, int width, int height,u16 color)
{
	plotLine(r,c,r,c+width,color);
	plotLine(r + height,c,r + height,c+width,color);
	plotLine(r,c,r+height,c,color);
	plotLine(r,c+width,r+height,c+width,color);
	}

/**
	Description: Draw a line between two points using Bresenham's 
	line algorithm
	
	Parameters: int r0 - the row of the beginning pixel
				int c0 - the column of the beginning piexel
				int r0 - the row of the ending pixel
				int c0 - the column of the ending piexel
				u16 color - the color of the line
	Return: None
*/
void plotLine(int r0, int c0, int r1, int c1, u16 color)
{
	int dr, dc, sc, sr, err ,err2;

	if(r0 <= r1)
	{
		dr = r1 - r0;
		sr = 1; 
	}else
	{
		dr = r0 - r1;
		sr = -1; 
	}

	if(c0 <= c1)
	{
		dc = c1 - c0;
		sc = 1;
	}else{
		dc = c0 - c1;
		sc = -1;
	}

	err = (dc>dr ? dc : -dr)>>1;
	 
	while(TRUE){
	setPixel(r0,c0,color);
	if (c0 == c1 && r0 == r1) break;
	err2 = err;
	if (err2 > -dc) { 
	err -= dr; 
	c0 += sc; 
	}
	if (err2 < dr) { 
	err += dc; 
	r0 += sr; 
	}
  }
	
}

/**
	Description: Wait till vblank
	
	Parameters: None
	Return: None
*/
void vid_vsync()
{
	while(REG_VCOUNT >= 160);   // wait till VDraw
	while(REG_VCOUNT < 160);    // wait till VBlank
}

/**
	Description: creat random colored pixel at random places
	Parameters: None
	Return: None
*/
void randomPixels()
{
	u16 r = rand() % 160;
	u16 c = rand() % 240;
	setPixel(r,c,randomColor());
}

/**
	Description: Generate a random color
	Parameters: None
	Return: u16 - the random generated color
*/
u16 randomColor()
{
	return RGB(rand() % 32,rand() % 32,rand() % 32);
}


/**
	Description: Draw a filled circle
	
	Parameters: int r0: the row number of the pixel at the center of the circle 
				int c0:  the column number of the pixel at the center of the circle
				int radius: the radius of the circle
				u16 color: the color of the circle
	Return: None
*/
void drawCircle(int r0, int c0 , int radius, u16 color)
{
	int c = radius;
  	int r = 0;
  	int radiusError = 1-c;
 
  while(c >= r)
  {

  	plotLine(r + r0, c + c0,  -r + r0,  c + c0, color);
  	plotLine(-r + r0,  -c + c0,  r + r0, -c + c0, color);
  	plotLine(c + r0, r + c0,  -c + r0,  r + c0, color);
    plotLine(-c + r0,  -r + c0, c + r0, -r + c0, color);
    r++;
    if (radiusError<0)
    {
      radiusError += (r << 1) + 1;
    }
    else
    {
      c--;
      radiusError += ((r - c + 1) << 1);
    }
  }
}

/**
	Description: Draw a hellow circle
	
	Parameters: int r0: the row number of the pixel at the center of the circle 
				int c0:  the column number of the pixel at the center of the circle
				int radius: the radius of the circle
				u16 color: the color of the circle
	Return: None
*/
void drawHollowCircle(int r0, int c0 , int radius, u16 color)
{
	int c = radius;
  	int r = 0;
  	int radiusError = 1-c;
 
  while(c >= r)
  {
  	setPixel( -r + r0,  -c + c0, color);
    setPixel(-c + r0,  -r + c0, color);
    setPixel( -r + r0,  c + c0, color);
    setPixel( -c + r0,  r + c0, color);
    setPixel(r + r0, c + c0,  color);
    setPixel(c + r0, r + c0,  color);
    setPixel(r + r0, -c + c0, color);
    setPixel( c + r0, -r + c0, color);

    r++;
    if (radiusError<0)
    {
      radiusError += (r << 1) + 1;
    }
    else
    {
      c--;
      radiusError += ((r - c + 1) << 1);
    }
  }
}

/**
	Description: Record wether a key down has happend. keyRecorded should be
	reset after handling the current recorded key down event.
	
	Parameters: None
	Return: None
*/
void getKeyRecord()
{
	if(KEY_DOWN_NOW(BUTTON_UP))
	{
		keyRecorded = keyRecorded|BUTTON_UP;
	}
	if(KEY_DOWN_NOW(BUTTON_DOWN))
	{
		keyRecorded = keyRecorded|BUTTON_DOWN;
	}
	if(KEY_DOWN_NOW(BUTTON_LEFT))
	{
		keyRecorded = keyRecorded|BUTTON_LEFT;
	}
	if(KEY_DOWN_NOW(BUTTON_RIGHT))
	{
		keyRecorded = keyRecorded|BUTTON_RIGHT;
	}
	if(KEY_DOWN_NOW(BUTTON_START))
	{
		keyRecorded = keyRecorded|BUTTON_START;
	}
	if(KEY_DOWN_NOW(BUTTON_SELECT))
	{
		keyRecorded = keyRecorded|BUTTON_SELECT;
	}
	if(KEY_DOWN_NOW(BUTTON_A))
	{
		keyRecorded = keyRecorded|BUTTON_A;
	}
	if(KEY_DOWN_NOW(BUTTON_B))
	{
		keyRecorded = keyRecorded|BUTTON_B;
	}
}

/**
	Description: reset key record
	
	Parameters: None
	Return: None
*/
void resetKeyRecord()
{
	keyRecorded = 0;
}

/**
	Description: Randomize a circle
	
	Parameters: struct Circle *circle: the address of the circle to be randomized
	Return: None
*/
void randomizeCircle(Circle *circle)
{

	circle->radius = rand()%12 + 3;
	circle->color = randomColor();
	circle->dr = rand()%31 - 15;
	circle->dc = rand()%31 - 15;
	circle->r = rand()%(160 - circle->radius);
	circle->c = rand()%240;
}


/**
	Description: Draw hollow circle with a Circle struct as parameter
	
	Parameters: Circle *circle - the struct Circle to be drawn
				u16 color - the color of the circle
	Return: None
*/
void drawHollowCircleWStruct(Circle *circle, u16 color)
{
	drawHollowCircle(circle->r,circle->c,circle->radius,color);
}


/**
	Code from CS2110 Resource
*/
void drawChar(int row, int col, char ch, unsigned short color)
{
	int r, c;
	for(r=0; r<8; r++)
	{
		for(c=0; c<6; c++)
		{
			if(fontdata_6x8[OFFSET(r, c, 6)+ch*48])
			{
				setPixel(row+r, col+c, color);
			}
		}
	}
}

/*Code from CS2110 Resource
 *-------------------------------------------------------------
 * I didn't code this in class but I will go over it next lecture
 *
 * You can call it like this:
 *
 * drawString(10, 10, "Hello!", YELLOW);
 *
 * or like this:
 * 
 * char *message = "This is a message.";
 * drawString(20, 5, message, RED);
 *
 * or like this:
 *
 * char buffer[41] = "This is a char array!";
 * drawString(30, 5, buffer, GREEN);
 * 
 */

void drawString(int row, int col, char *str, unsigned short color)
{
	while(*str)
	{
		drawChar(row, col, *str++, color);
		col +=6;

	}
}


/**
	Description: draw a character with an extra parameter size
	
	Parameters: int row
				int col
				char ch 
				unsigned short color
				u16 size
	Return: None
*/
void drawCharWSize(int row, int col, char ch, unsigned short color, u16 size)
{
	int r, c;
	for(r=0; r<8; r++)
	{
		for(c=0; c<6; c++)
		{
			if(fontdata_6x8[OFFSET(r, c, 6)+ch*48])
			{
				drawHollowRect(row+(r*size), col+(c*size),size, size , color);
			}
		}
	}
}


/**
	Description: draw string with an extra parameter size
	
	Parameters: int row
				int col
				char ch 
				unsigned short color
				u16 size
	Return: None
*/
void drawStringWSize(int row, int col, char *str, unsigned short color, u16 size)
{
	while(*str)
	{
		drawCharWSize(row, col, *str++, color, size);
		col +=6*size;

	}
}

/**
	Description: Convert int to string
	
	Parameters: char *str - the address of space reserved 
				int num - the number to be converted
	Return: None
*/
void toString(char *str, int num)
{
    int i, rem, len = 0, n;
    n = num;
    if(!n)
    {
    	str[0] = '0';
    	str[1] = '\0';
    	return;
    }
	while (n)
    {
        len++;
        n /= 10;
    }

    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }

    str[len] = '\0';

}



void drawRect(int row, int col, int height, int width, const unsigned short color)
{
	int r;
	for(r=0; r<height; r++)
	{
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)];
		DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
	}
}


void drawPartialBGDMA(int row, int col, int height, int width, const unsigned short* color)
{
	int r;
	for(r=0; r<height; r++)
	{
		DMA[3].src = &color[OFFSET(row+r, col, 240)];
		DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)];
		DMA[3].cnt = width | DMA_ON ;
	}
}

void drawBGDMA(const unsigned short* color)
{
		DMA[3].src = color;
		DMA[3].dst = videoBuffer;
		DMA[3].cnt = 240*160 | DMA_ON ;	
}

void drawImage3(int row, int col, int height, int width, const unsigned short* color)
{
	int r;
	for(r=0; r<height; r++)
	{
		DMA[3].src = color + width * r;
		DMA[3].dst = &videoBuffer[OFFSET(row+r, col, 240)];
		DMA[3].cnt = width | DMA_ON ;
	}
}

void drawAim(Aim* aim, u16 color)
{
	drawHollowCircleWStruct(&(aim->circle),color);
	setPixel(aim->circle.r,aim->circle.c,color);
	setPixel(aim->circle.r + 1,aim->circle.c,color);
	setPixel(aim->circle.r - 1,aim->circle.c,color);
	setPixel(aim->circle.r,aim->circle.c + 1,color);
	setPixel(aim->circle.r,aim->circle.c - 1,color);
}

void drawEnemy(EnemyList *enemyList, const unsigned short* color1,const unsigned short* color2,const unsigned short* color3,const unsigned short* color4)
{
	for(int i = 0; i < (enemyList->size); i++)
	{
		switch(enemyList->enemies[i].hp)
		{
			case 4:drawImage3(enemyList->enemies[i].r, enemyList->enemies[i].c, ENEMYSIZE , ENEMYSIZE , color4);
			break;
			case 3:drawImage3(enemyList->enemies[i].r, enemyList->enemies[i].c, ENEMYSIZE , ENEMYSIZE , color3);
			break;
			case 2:drawImage3(enemyList->enemies[i].r, enemyList->enemies[i].c, ENEMYSIZE , ENEMYSIZE , color2);
			break;
			case 1:drawImage3(enemyList->enemies[i].r, enemyList->enemies[i].c, ENEMYSIZE , ENEMYSIZE , color1);
			break;
		}
	}
}

void randomizeEnemy(Enemy *enemy)
{
	enemy->dr = rand()%4 - 17;
	enemy->r = 120 + rand()%19;
	if(rand()%2 == 1)
	{ 
		enemy->c = 200 + rand()%20;
		enemy->dc = rand()%3 - 5;
	}
	else
	{
	  enemy->c = rand()%20;
	  enemy->dc = rand()%3 + 2;	  
	}

	enemy->hp = rand()%4 + 1;
}

void updateEnemy(EnemyList *enemyList, int *timeLeft)
{
	for(int i = 0; i < (enemyList->size); i++)
	{
		enemyList->enemies[i].r +=enemyList->enemies[i].dr;
		enemyList->enemies[i].dr += 1;
		enemyList->enemies[i].c +=enemyList->enemies[i].dc;

		if(enemyList->enemies[i].r > 160)
		{
			(*timeLeft)--;
			randomizeEnemy(&enemyList->enemies[i]);
		}
		else if (enemyList->enemies[i].r < 0)
		{
			enemyList->enemies[i].r = 0;
			enemyList->enemies[i].dr = -enemyList->enemies[i].dr;
		}

		if(enemyList->enemies[i].c > 240 - ENEMYSIZE)
		{
			enemyList->enemies[i].c = 240 - ENEMYSIZE;
			enemyList->enemies[i].dc = -enemyList->enemies[i].dc;
		}
		else if(enemyList->enemies[i].c < 0)
		{
			enemyList->enemies[i].c = 0;
			enemyList->enemies[i].dc = -enemyList->enemies[i].dc;
		}
	}
}

void shoot(EnemyList *enemyList, Aim *aim, Bam *bam,BoostItem *boostItem , int *score, int *timeLeft, int *factor, int *feverTime)
{
	for(int i = 0; i < (enemyList->size); i++)
	{
		if(checkCollision(&enemyList->enemies[i],aim))
		{

			bam->frame =  30;
			bam->r = enemyList->enemies[i].r - 2;
			bam->c = enemyList->enemies[i].c - 2;
			if(enemyList->enemies[i].hp == 4)
			{
				(*timeLeft)--;
				if(*score >= 10)
				*score -= 10;
				else
				*score = 0;
				randomizeEnemy(&enemyList->enemies[i]);
			}
			else
			{
				enemyList->enemies[i].hp--;
				*score += (1 << *factor);
				if(!enemyList->enemies[i].hp)
				{
					randomizeEnemy(&enemyList->enemies[i]);
				}
			}
		}
	}

	if(boostItem->active)
	{
		if(checkBoostItem(boostItem,aim))
		{
			(*feverTime) += 11;
			(*factor)++;
			boostItem->active = FALSE;
		}
	}
}

u8 checkCollision(Enemy *enemy, Aim *aim)
{
	int d = (ENEMYSIZE>>1) + 5;
	int dr = abs(enemy->r + (ENEMYSIZE>>1) - aim->circle.r);
	int dc = abs(enemy->c + (ENEMYSIZE>>1) - aim->circle.c);

	if(dr <= d && dc <= d)
	{
		if(d*d >= (dr*dr + dc*dc))
		{	
			return TRUE;
		}
	}
	return FALSE;

}

u8 checkBoostItem(BoostItem *boostItem, Aim *aim)
{
	int d = (ENEMYSIZE>>1) + 5;
	int dr = abs(boostItem->r + (ENEMYSIZE>>1) - aim->circle.r);
	int dc = abs(boostItem->c + (ENEMYSIZE>>1) - aim->circle.c);

	if(dr <= d && dc <= d)
	{
		if(d*d >= (dr*dr + dc*dc))
		{	
			return TRUE;
		}
	}
	return FALSE;

}

void drawBam(Bam *bam, const unsigned short *color)
{
	
	if((bam->frame)>0)
	{
		drawImage3(bam->r, bam->c, 25 , 25 , color);
		(bam->frame)--;
	}
}

void moreEnemy(EnemyList *enemyList)
{

	if((enemyList->size) < 6)
	{
			enemyList->size++;
			randomizeEnemy(&enemyList->enemies[enemyList->size-1]);
	}

}

void drawBoostItem(BoostItem *boostItem, const unsigned short *color)
{
	
	if(boostItem->active)
	{
		drawImage3(boostItem->r, boostItem->c, ENEMYSIZE , ENEMYSIZE, color);
	}
}

void updateBoostItem(BoostItem *boostItem)
{
	if(boostItem->active)
	{
		boostItem->c += 3;
		boostItem->r += boostItem->offRange;
		boostItem->offRange += boostItem->dRange;
		if((boostItem->offRange) > (boostItem->maxRange) || (boostItem->offRange < -(boostItem->maxRange)))
			boostItem->dRange = -(boostItem->dRange);
		if((boostItem->c) > 239 - ENEMYSIZE)
			{
				boostItem->active = FALSE;
			}
	}
}

void generateBoostItem(BoostItem *boostItem)
{
	boostItem->active = TRUE;
	boostItem->c = -10;
	boostItem->r = rand()%30+30;
	boostItem->dRange = 1;
	boostItem->maxRange = 5+rand()%5;
	boostItem->offRange = 0;	
}
