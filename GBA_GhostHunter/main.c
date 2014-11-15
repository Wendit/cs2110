#include "mylib.h"
#include "bg.h"
#include "face1.h"
#include "face2.h"
#include "face3.h"
#include "bam.h"
#include "face0.h"
#include "boost1.h"
#include "bg2.h"
#include "bg3.h"
#include <string.h>

int main(void);
void menuScreen();
void gameScreen();
void scoreScreen();

char strScore[4];

int main(void) {
	//set dispy mode	
	(REG_DISPCNT) = (BG2_ENABLE) | (MODE3);
	while(TRUE){
		menuScreen();
		gameScreen();
		scoreScreen();
		}	
}

void menuScreen()
{
	u8 menuScreenDisplay = TRUE;
	u16 counter = TIMER1;
	drawBGDMA(bg2);
	drawStringWSize(60,5,"Ghost hunter!",WHITE,3);
	while(menuScreenDisplay)
	{
		vid_vsync();
		counter--;
		if(counter == 30)
		{
			drawString(120,60,"Press start to begin!",WHITE);
		}
		else if(!counter)
		{
			counter = TIMER1;
			drawPartialBGDMA(120,60,20,200,bg2);
		}
		if(KEY_DOWN_NOW(BUTTON_START))
		menuScreenDisplay = FALSE;
	}
}

void gameScreen()
{
	u8 gameScreenDisplay = TRUE;
	drawBGDMA(bg);
	int timeLeft = 120;
	score = 0;
	int factor = 0;
	int feverTime = 0;
	int timer1 = TIMER1;
	int counter5sec = 5;
	int boost = FALSE;
	strcpy(strScore,"0");
	char strTime[4] = "120\0"; 

	//enemies
	EnemyList enemyList;
	enemyList.size = 2;
	for(int i = 0; i < enemyList.size; i++)
	{
		randomizeEnemy(&enemyList.enemies[i]);
	}

	BoostItem boostItem;
	boostItem.active = FALSE;
	boostItem.r = 0;
	boostItem.c = 0;
	boostItem.maxRange = 0 ;
	boostItem.dRange = 0;
	boostItem.offRange = 0;

	Aim aim;
	aim.circle.r = 79;
	aim.circle.c = 119;
	aim.circle.radius = 6;
	aim.circle.color = WHITE;
	u8 speed;

	u8 skip = 3;

	Bam bamm;
	bamm.r = 0;
	bamm.c = 0;
	bamm.frame = 0;

	while(gameScreenDisplay)
	{
			vid_vsync();
			timer1--;
			if(!timer1)
			{
				timer1 = TIMER1;
				timeLeft--;
				counter5sec--;
				toString(strTime,timeLeft);
				toString(strScore,score);
				if(!counter5sec)
				{
					moreEnemy(&enemyList);
					if(!boost)
					{
						boost = TRUE;
					}
					else{
						boost = FALSE;
						generateBoostItem(&boostItem);
					}
					counter5sec = 5;
				}
				if(feverTime)
				{
					feverTime--;
					if(!feverTime)
					factor = 0;
				}
			}
			//clear trace
			drawPartialBGDMA(10,20,20,20,bg);
			drawPartialBGDMA(10,160,20,40,bg);
			drawPartialBGDMA(aim.circle.r-6, aim.circle.c-6,13, 13, bg);
			drawPartialBGDMA(bamm.r, bamm.c, 25 , 25 , bg);
			if(boostItem.active)
			{
				drawPartialBGDMA(boostItem.r, boostItem.c, 20 , 20 , bg);
			}
			
			for(int i = 0; i < enemyList.size; i++)
			{
				drawPartialBGDMA(enemyList.enemies[i].r, enemyList.enemies[i].c,ENEMYSIZE, ENEMYSIZE, bg);
			}

			//get input
			getKeyRecord();
			if(KEY_DOWN_NOW(BUTTON_B))
			{
				speed = 2;
			}else
			{
				speed = 4;
			}
			if(KEY_DOWN_NOW(BUTTON_LEFT))
				aim.circle.c -= speed;
			if(KEY_DOWN_NOW(BUTTON_RIGHT))
				aim.circle.c += speed;
			if(KEY_DOWN_NOW(BUTTON_UP))
				aim.circle.r -= speed;
			if(KEY_DOWN_NOW(BUTTON_DOWN))
				aim.circle.r += speed;
				
			//move aim
			if(aim.circle.r < 0)
			{
				aim.circle.r = 159;
			}
			else if(aim.circle.r > 159)
			{
				aim.circle.r = 0;
			}
			if(aim.circle.c < 0)
			{
				aim.circle.c = 259;
			}
			else if(aim.circle.c > 259)
			{
				aim.circle.c = 0;
			}

			//only update enemy every 3 frames
			if(!skip){
				skip = 3;
				if(KEY_DOWN_RECORDED(BUTTON_A))
				{
					shoot(&enemyList, &aim, &bamm, &boostItem, &score, &timeLeft, &factor,&feverTime);
					resetKeyRecord();
				}	
				updateEnemy(&enemyList, &timeLeft);
				updateBoostItem(&boostItem);
			}
			else{
				skip --;
			}
			
			drawEnemy(&enemyList,face1,face2,face3,face0);
			if(feverTime)
			drawAim(&aim,randomColor());
			else
			drawAim(&aim,WHITE);
			drawBam(&bamm,bam);
			drawBoostItem(&boostItem,boost1);
			drawString(10,10,"S:",WHITE);
			drawString(10,20,strScore,WHITE);
			drawString(10,160,"T:",WHITE);
			drawString(10,170,strTime,WHITE);



			if(timeLeft<0)
				gameScreenDisplay = FALSE;		

	}
}

	void scoreScreen()
	{
		u8 scoreScreenDisplay = TRUE;
		u16 counter = TIMER1;
		drawBGDMA(bg3);
		drawStringWSize(30,40,"Your score is:",WHITE,2);
		drawStringWSize(60,80,strScore,WHITE,3);
		while(scoreScreenDisplay)
		{
			vid_vsync();
			counter--;
			if(counter == 30)
			{
				drawString(100,40,"Press select to play again!",WHITE);
			}
			else if(!counter)
			{
				counter = TIMER1;
				drawPartialBGDMA(100,40,20,200,bg3);
			}
			if(KEY_DOWN_NOW(BUTTON_SELECT))
			scoreScreenDisplay = FALSE;
		}
	}
