#include "arial_red.h"
#include "arial_yellow.h"
#include "copperstone_blue.h"
#include "stone_gray.h"
#include "mylib.h"

/* The delimiter if you will of the first row of the image is this color */
#define PINK 0x7c1f

// You may not change any declarations or types here or the functions.
typedef struct fffont
{
    const u16* image_data; /* Backing image data */
    u16 charpos[10]; /* X coordinate of the first column of the character. There are 10 characters and therefore 10 char positions.*/
    u16 charwidth[10]; /* Widths of each individual character. There are 10 characters and therefore 10 char widths*/
    int height; /* Height of the image */
    int width; /* Width of the image */
} fffont;


void initalize_fffont_helper(fffont* font);



/* Initialize ALL the components of the fffont struct using the given parameters and the calculated char positions and char widths arrays.

   To calculate the values for the charpos and charwidth arrays you will need to look at the colors in the first
   row of the image parameter. The exact color value of the pink delimiter is given to you as a #define called PINK at the top of this file. 
   Use this knowledge as well as the information covered in the instruction pdf to calculate the beginning X coodinate 
   and width of each character in the image.  

   charpos[0] should contain the X coordinate (that is the column) of the '0' character in the inputted image.
   charwidth[0] should contain the width of the '0' character
   charpos[1] should contain the X coordinate (that is the column) of the '1' character in the inputted image..
   charwidth[1] should contain the width of the '1' character
   etc.

   If you are unable to get this function to work, a helper function has been provided that will allow you to work on the other sections
   of this timed lab. See main() and initalize_fffont_helper() for more details. 
*/
void initalize_fffont(fffont* font, const u16* image, int widthOfImage, int heightOfImage)
{
        // Your code goes here
      int currentPos=0;
      font->image_data = image;
      font->height = heightOfImage;
      font->width = widthOfImage;
      for(int i = 0; i < 10;i++)
      {
        font->charpos[i] = currentPos;
        while(*image != PINK)
        {
          font->charwidth[i]++;
          image++;
          currentPos++;
          if(currentPos == widthOfImage -1 )
            break;
        }
        while(*image == PINK)
        {
          image++;
          currentPos++;
        }

      }
}




/* You must draw the character with DMA here.

   Remember that the digit passed into this function is in ASCII. The character '0' in ASCII is 48, '1' is 49, '2' is 50, etc. 
   In case you have forgotten how to convert from a number in ASCII to its integer value, refer back to Homework 2 

   The x and y values are the location on the screen you should be drawing the character at.
*/

/* Set pixel solutions receive no credit*/
void draw_fffchar(fffont* font, int x, int y, char digit)
{
    int y1;
    int n = digit - '0';
    for(y1 = 0; y1< (font->height); y1++)
    {
      DMA[3].src = (font->image_data) + (font->width) * y1 + (font->charpos[n]);
      DMA[3].dst = &videoBuffer[x + (y + y1)*240];
      DMA[3].cnt = font->charwidth[n] | DMA_ON ;
    }

}




/* Draws an fffstring starting at x and y.
   
   fffstring is guaranteed to contain only the characters 0-9 and the new line character '\n'. 
   When you encounter a new line you must start drawing at the next line at the same starting x coordinate. 

   The fffstring will be NULL terminated. 
*/ 
void draw_fffstring(fffont* font, const char* fffstring, int startx, int y)
{
  int x = startx;
  while(*fffstring)
  {
    if(*fffstring == '\n')
    {
      y += font-> height;
      x = startx;
    }
    else{
    draw_fffchar(font , x, y, *fffstring);
    int n = *fffstring -'0';
    x +=font->charwidth[n];
    }
    fffstring++;
  }
}




int main(void)
{
    /* Initialize REG_DISPCNT (you should not modify this code) */
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    /* Declare fffont structs here (you should not modify this code) */
        fffont c_b_font;
        fffont a_r_font;
        fffont a_y_font;
        fffont s_g_font;

        fffont c_b_font_helper; /* This fffont struct will be initialized by calling a special helper function that has been written with
                                   predefined hard coded values for the copperstone blue font. If you are unable to get the 
                                   intialize_fffont function to work, you may use this ffffont struct to test your draw_fffchar and
                                   draw_fffstring functions */


    /* Initialize them by calling the intialize fffont function (you should not modify this code) */
        initalize_fffont(&c_b_font, copperstone_blue, COPPERSTONE_BLUE_WIDTH, COPPERSTONE_BLUE_HEIGHT);
        initalize_fffont(&a_r_font, arial_red, ARIAL_RED_WIDTH, ARIAL_RED_HEIGHT);
        initalize_fffont(&a_y_font, arial_yellow, ARIAL_YELLOW_WIDTH, ARIAL_YELLOW_HEIGHT);
        initalize_fffont(&s_g_font, stone_gray, STONE_GRAY_WIDTH, STONE_GRAY_HEIGHT);

        initalize_fffont_helper(&c_b_font_helper); /* The c_b_font_helper struct is initalized with hardcoded values for the copperstone blue font. 
                                                      If you are unable to get initalize_fffont to work, use this struct to test your draw_fffchar and
                                                      draw_fffstring functions */


    /* To test your funtions, call draw_fffstring with one of the five fffonts defined above, a string of characters to draw, an x value and a y value. 
        You may change this code to test your functions. The test code is only an example function call to draw_fffstring. */
        char *my_string = "09182\n73645\n37285";
        int x = 50;
        int y = 20;
        draw_fffstring(&a_r_font, my_string, x, y);
        while(1);
}




/* A predefined helper function for your convenience during testing. This is to help you test your draw_fffchar and draw_fffstring if you cannot get the
   initalize_fffont function to work. It contains the hard coded values for the copperstone_blue font. You may not call this function from 
   inside initalize_fffont. You may not use the values contained in this function to hard code values in initalize_fffont. */
void initalize_fffont_helper(fffont* font) {
        font->image_data = copperstone_blue;
        font->height = COPPERSTONE_BLUE_HEIGHT;
        font->width = COPPERSTONE_BLUE_WIDTH;
        font->charpos[0] = 0;
        font->charwidth[0] = 23;
        font->charpos[1] = 37;
        font->charwidth[1] = 9;
        font->charpos[2] = 62;
        font->charwidth[2] = 22;
        font->charpos[3] = 93;
        font->charwidth[3] = 22;
        font->charpos[4] = 124;
        font->charwidth[4] = 22;
        font->charpos[5] = 155;
        font->charwidth[5] = 22;
        font->charpos[6] = 186;
        font->charwidth[6] = 22;
        font->charpos[7] = 217;
        font->charwidth[7] = 22;
        font->charpos[8] = 248;
        font->charwidth[8] = 22;
        font->charpos[9] = 279;
        font->charwidth[9] = 21;

}





