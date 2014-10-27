/**
	File name: main.c
	Author: Wendi Tang
	History: v0.1 completed by WT 2014/10/21 
	Description: This file contains the main function for the
	hello world game.
*/
#include "mylib.h"

int main(void);
void menuScreen();
void difficultyScreen();
void gameScreen();
void scoreScreen();


int main(void) {
	//set dispy mode	
	(REG_DISPCNT) = (BG2_ENABLE) | (MODE3);
	while(TRUE){
		score = 0;
		menuScreen();
		difficultyScreen();
		gameScreen();
		scoreScreen();
		}	
}



void gameScreen()
{
	u8 runGame = TRUE;
	//draw white background
	drawRect(0,0,240,160,WHITE);


	int counter1 = TIMER1;
	int counter2 = TIMER4;


	//Creat and initialize Me
	struct Me me;
	initializeMe(&me);



	 //Creat boost item
	struct Boost boostItem;
	randomizeBoostItem(&boostItem);

	//Creat obstacles
	int circleNum = 3;
	 switch(difficulty)
	 {
	 	case 0: circleNum = 3;
				break;
	 	case 1: circleNum = 5;
	 			break;
	 	case 2: circleNum = 7;
	 			break;
	 	case 3: circleNum = 10;
	 			break;
	 }	
	struct Circle rc[circleNum];
	for(int i = 0; i < circleNum; i++)
	{
		generateCircle(&rc[i]);
	}

	//score string
	char strScore[3]={'0','0','0'};
	drawString(5,100,strScore,BLACK);

	resetKeyRecord();
	while(runGame)
	{
		counter1--;
		counter2--;

		vid_vsync();
		if(!counter1)
		{
			counter1 = TIMER1;
			score++;
			if(!((score + 1) % 5))
			{
				randomizeBoostItem(&boostItem);
				boostItem.active = TRUE;

			}
			if(score > 999)
			{
				score = 999;
			}
			//eliminate score string trace
			drawString(5,100,strScore,WHITE);
			toString(strScore,score);
		}
		if(!counter2)
		{	counter2 = TIMER4;
			for(int i = 0; i < circleNum; i++)
			{
				updateGameCircle(&rc[i]);
			}
		}

		//eliminate trace
		drawMe(&me, WHITE);
		//handle button events
		if(KEY_DOWN_NOW(BUTTON_A))
		{
			me.core.r -= 3;//jump height
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT))
		{
			me.core.c -= 1;//jump height
		}
		if(KEY_DOWN_NOW(BUTTON_RIGHT))
		{
			me.core.c += 1;//jump height
		}

		updateMe(&me);

		for(int i = 0; i < circleNum; i++)
		{
			checkCollisionWithCircle(&rc[i],&me);
		}


		if(boostItem.active)
		{
			drawBoostItem(&boostItem,RED);
			checkCollisionWithBoostItem(&boostItem,&me);
		}

		if(!me.hp)
		{
			runGame = FALSE;
		}

		drawString(5,100,strScore,BLACK);
	}

}

void scoreScreen()
{
	u8 displayScore = TRUE;
	char strScore[3];
	int counter1 = TIMER1;

	toString(strScore,score);
	//draw white background
	drawRect(0,0,240,160,WHITE);
	drawString(40,60,"Your score is:",BLACK);
	drawStringWSize(60,75,strScore,BLACK,3);

		while(displayScore)
		{	
			vid_vsync();
			counter1--;
				if(counter1 == 30)
				drawString(100,40,"Press start to start over!",BLACK);
				else if(counter1 == 0)
				{
					drawString(100,40,"Press start to start over!",WHITE);
					counter1 = TIMER1;	
				}
			if(KEY_DOWN_NOW(BUTTON_START))
				displayScore = FALSE;
				
		}
	}


void menuScreen()
{

	u8 runMenu = TRUE;
	//draw white background
	drawRect(0,0,240,160,WHITE);

	//counters for 1s, 0.5s, 0.1s based on frames
	u16 counter1  = TIMER4;
	u16 counter2 = TIMER1;


	//the number of total circles
	int circleNum = 10;

	//Creat and initialize stringbitmap
	struct StringBitmap helloWorld;
	initializeStringBitMap(&helloWorld,60,30,3,BLACK,"Survive!!! ",0,0);

	//Creat and initialize circles
	struct Circle rc[circleNum];
	for(int i = 0; i < circleNum; i++)
	{
		randomizeCircle(&rc[i]);
	}

	//main game loop
	while (runMenu) {
		vid_vsync();
		//counter decrease on each frame
		counter1--;
		counter2--;

		//get key down information 
		getKeyRecord();

		if(!counter1)
		{
		//reset conter
		counter1 = TIMER4;

		//key check
		if(KEY_DOWN_RECORDED(BUTTON_START))
		{
			runMenu = FALSE;
		}

		resetKeyRecord();

		//update circles
		for(int i = 0; i < circleNum; i++)
		{
			updateCircle(&rc[i]);
		}

		//draw string
		drawStringWSize(helloWorld.r,helloWorld.c,helloWorld.str,helloWorld.color,helloWorld.size);

		}

		if(counter2 > 30)
		drawString(100,50,"Press start to begin!",BLACK);
		else if(counter2 > 0)
		{
		drawString(100,50,"Press start to begin!",WHITE);
		}
		else if(!counter2)
		{
			counter2 = TIMER1;	
		}

		
	}
}

void difficultyScreen()
{
	u8 diffcultyMenu = TRUE;

	int counter1 = TIMER1;
	//draw white background
	drawRect(0,0,240,160,WHITE);
	drawString(40,40,"Please choose a difficulty:",BLACK);
	drawString(100,40,"Press UP or DOWN to choose",BLACK);
	drawStringWSize(60,65,"PYTHON",BLACK,3);

		while(diffcultyMenu)
		{	
			vid_vsync();
			counter1--;
			getKeyRecord();

			if(!counter1)
			{
			counter1 = TIMER1;
			if(KEY_DOWN_RECORDED(BUTTON_UP))
			{
				difficulty--;
				drawRect(60,55,160,30,WHITE);
				if(difficulty < 0)
				{
					difficulty = 3;
				}
			}
			if(KEY_DOWN_RECORDED(BUTTON_DOWN))
			{
				difficulty++;
				drawRect(60,55,160,30,WHITE);
				if(difficulty > 3)
				{
					difficulty = 0;
				}
			}

			if(difficulty == 0)
			{
				drawStringWSize(60,65,"PYTHON",BLACK,3);
			}
			else if(difficulty == 1)
			{
				drawStringWSize(60,65,"JAVA",BLACK,3);
			}
			else if(difficulty == 2)
			{
				drawStringWSize(60,65,"C",BLACK,3);
			}
			else if(difficulty == 3)
			{
				drawStringWSize(60,65,"ASSEMBLY",BLACK,3);
			}

			resetKeyRecord();

			}

				if(KEY_DOWN_NOW(BUTTON_START))
				diffcultyMenu = FALSE;
			
		}

}

