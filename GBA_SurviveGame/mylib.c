/**
	File name: mylib.c
	Author: Wendi Tang
	History: v0.1 completed by WT 2014/10/21 
	Description: This file is the game library. It contains 
	the function implementations.
*/
#include "mylib.h"

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
	Description: Draw a filled rectangle
	
	Parameters: int r - the row of the pixel at the upper 
				left corner of the rectangle
				int c - the column of the piexel at the upper
				left coner of the rectangle 
				int width - the width of the rectangle
				int height - the height of the rectangle
				u16 color - the color of the rectangle
	Return: None
*/
void drawRect(int r, int c, int width, int height, u16 color)
{
	int i = r;
	for(; i < r + height;i++)
	{
		plotLine(i,c,i,c+width,color);
	}
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
	Description: Draw the given string
	
	Parameters: int r - the row of the pixel at the upper left corner
				int c - the column of the pixel at the upper right coner
				char* str - the string to be drawn
				u16 size - the width of the line used to draw the string
				u16 color - the color of the string
	Return: None
*/
// void drawString(int r, int c , char* str,u16 size, u16 color)
// {
// 	char* cha = str;
// 	while (*cha){
// 		drawChar(r,c,*cha++,size,color);
// 		c += size * 5;
// 	} 
	
// }


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
    setPixel(r + r0, c + c0,  color);
    setPixel(c + r0, r + c0,  color);
    setPixel(r + r0, -c + c0, color);
    setPixel( c + r0, -r + c0, color);
    setPixel( -r + r0,  -c + c0, color);
    setPixel(-c + r0,  -r + c0, color);
    setPixel( -r + r0,  c + c0, color);
    setPixel( -c + r0,  r + c0, color);
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
void randomizeCircle(struct Circle *circle)
{

	(*circle).radius = rand()%12 + 3;
	(*circle).color = randomColor();
	(*circle).dr = rand()%31 - 15;
	(*circle).dc = rand()%31 - 15;
	(*circle).r = rand()%(160 - (*circle).radius);
	(*circle).c = rand()%240;
}

void generateCircle(struct Circle *circle)
{

	//eliminate trace
	drawHollowCircleWStruct(circle, WHITE);

	(*circle).r = rand()%(160 - (*circle).radius);
	(*circle).radius = rand()%10 + 1;
	(*circle).color = randomColor();
	(*circle).dr = rand()%15 - 7;

	if(rand()%2 == 0)
	{
		(*circle).c = (*circle).radius;
		(*circle).dc = rand()%6 + 1;
	}
	else
	{
		(*circle).c = (239 - (*circle).radius);
		(*circle).dc = -(rand()%6 + 1);
	}
}


void drawHollowCircleWStruct(struct Circle *circle, u16 color)
{
	drawHollowCircle((*circle).r,(*circle).c,(*circle).radius,color);
}
/**
	Description: update a circle
	
	Parameters: struct Circle *circle: the address of the circle to be updated
	Return: None
*/
void updateCircle(struct Circle *circle)
{
			//eliminate trace
			drawHollowCircleWStruct(circle, WHITE);

			//change position
			(*circle).c += (*circle).dc;
			(*circle).r += (*circle).dr;

			//wrap
			if((*circle).c > (239 + (*circle).radius))
				(*circle).c = (*circle).radius;
			else if((*circle).c < -(*circle).radius)
				(*circle).c = 239 + (*circle).radius;

			//bounce
			if((*circle).r < (*circle).radius){
				(*circle).r = (*circle).radius;
				(*circle).dr = -(*circle).dr;
			}
			else if((*circle).r > 160 - (*circle).radius){
				(*circle).r = 160 - (*circle).radius;
				(*circle).dr = -(*circle).dr;
			}
			drawHollowCircleWStruct(circle, (*circle).color);
}

void updateGameCircle(struct Circle *circle)
{

	if((*circle).c >= (*circle).radius && (*circle).c <= (239 - (*circle).radius)){
			//eliminate trace
			drawHollowCircleWStruct(circle, WHITE);

			//change position
			(*circle).c += (*circle).dc;
			(*circle).r += (*circle).dr;

			//bounce
			if((*circle).r < (*circle).radius){
				(*circle).r = (*circle).radius;
				(*circle).dr = -(*circle).dr;
			}
			else if((*circle).r > 160 - (*circle).radius){
				(*circle).r = 160 - (*circle).radius;
				(*circle).dr = -(*circle).dr;
			}
			drawHollowCircleWStruct(circle, (*circle).color);
	}
	else
	{
		generateCircle(circle);
	}
}

void checkCollisionWithCircle(struct Circle *circle, struct Me *me)
{
	int d = (*circle).radius + (*me).core.radius + ((*me).wallNum<<1);
	int dr = abs((*circle).r - (*me).core.r);
	int dc = abs((*circle).c - (*me).core.c);

	if(dr <= d && dc <= d)
	{
		if(d*d <= (dr*dr + dc*dc))
		{
			if((*me).wallNum)
			{
				drawMe(me,WHITE);
				(*me).wallNum--;

			}
			else
			{
				(*me).hp--;
				switch((*me).hp)
				{
					case 3:(*me).core.color = GREEN;
					break;
					case 2:(*me).core.color = RED;
					break;
					case 1:(*me).core.color = BLACK;
					break;
				}
			}

			generateCircle(circle);
		}
	}

}

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

/*
 *
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

void drawStringWSize(int row, int col, char *str, unsigned short color, u16 size)
{
	while(*str)
	{
		drawCharWSize(row, col, *str++, color, size);
		col +=6*size;

	}
}

void initializeStringBitMap(struct StringBitmap *stringBitmap, int r, int c, u16 size, u16 color, char* str, 
	int dr, int dc)
{
	(*stringBitmap).str = str;
	(*stringBitmap).size = size;
	(*stringBitmap).color = color;
	(*stringBitmap).r = r;
	(*stringBitmap).c = c;
	(*stringBitmap).dr = dr;
	(*stringBitmap).dc = dc;
	// *stringBitmap.width = 6*13**stringBitmap.size;
	// *stringBitmap.length = 5**stringBitmap.size + 1;
}

void initializeMe(struct Me *me)
{
	(*me).core.radius = 2;
	(*me).core.color = BLUE;
	(*me).core.dr = 0;
	(*me).core.dc = 0;
	(*me).core.r = 79;
	(*me).core.c = 119;
	(*me).wallNum = 2;
	(*me).hp = 4;
}

void updateMe(struct Me *me)
{

			//change position
			(*me).core.c += (*me).core.dc;
			(*me).core.r += (*me).core.dr;
			(*me).core.r += 1;//gravity

			//wrap
			if((*me).core.c > (239 + (((*me).wallNum)<<1)))
				(*me).core.c = (((*me).wallNum)<<1);
			else if((*me).core.c < -(((*me).wallNum)<<2))
				(*me).core.c = 239 + (((*me).wallNum)<<1);

			//bounce
			if((*me).core.r < (((*me).wallNum)<<1)){
				(*me).core.r = (((*me).wallNum)<<1);
				(*me).core.dr = -(*me).core.dr;
			}
			else if((*me).core.r > 160){
				(*me).hp = 0;
			}

			drawMe(me, (*me).core.color);
}

void drawMe(struct Me *me, u16 color)
{
	drawCircle((*me).core.r,(*me).core.c,(*me).core.radius,color);
	if(color != WHITE)
	{
	for(int i = 1;i <= (*me).wallNum;i++){
		drawHollowCircle((*me).core.r,(*me).core.c,(*me).core.radius + (i<<1),(color >> i ));
		}
	}
	else
	{
		for(int i = 1;i <= (*me).wallNum;i++){
		drawHollowCircle((*me).core.r,(*me).core.c,(*me).core.radius + (i<<1),WHITE);
		}
	}

}

void toString(char str[], int num)
{
    int i, rem, len = 0, n;
    n = num;
	while (n != 0)
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

void randomizeBoostItem(struct Boost *boost)
{
	drawBoostItem(boost,WHITE);
	(*boost).r = rand()%145 + 10;
	(*boost).c = rand()%225 + 10;
	(*boost).active = FALSE;
}

void checkCollisionWithBoostItem(struct Boost *boost, struct Me *me)
{	
	int d = 3 + (*me).core.radius + ((*me).wallNum<<1);
	int dr = abs((*boost).r - (*me).core.r);
	int dc = abs((*boost).c - (*me).core.c);

	if(dr <= d && dc <= d)
	{
		if(d*d <= (dr*dr + dc*dc))
		{	
			if((*me).wallNum < 4)
				(*me).wallNum++;
			else
				score += 50;
			randomizeBoostItem(boost);
		}
	}	

}

void drawBoostItem(struct  Boost *boost,u16 color)
{
		drawHollowCircle((*boost).r, (*boost).c , 3 , color);
		setPixel((*boost).r,(*boost).c,color);
		setPixel((*boost).r+1,(*boost).c,color);
		setPixel((*boost).r-1,(*boost).c,color);
		setPixel((*boost).r,(*boost).c+1,color);
		setPixel((*boost).r,(*boost).c-1,color);
}

