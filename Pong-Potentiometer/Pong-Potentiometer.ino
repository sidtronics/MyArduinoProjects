#include <U8glib.h>

// Use the emum type to create unique values for our constants
enum {
    POSITION = 0,
    SOUND,
    SPEED,
    SKEW,
    SIZE,
    LAST
};

// Define and initialize our data structure for the parameters.
// The paddle position is changed simply by rotating the RE shaft when in normal game mode.
// There are 4 adjustable (i.e. customizable) parameters: sound, ball speed, skew and paddle size.
// To enter the adjustment/customization mode: press the RE switch. The parameters will cycle sequentially
// from sound->speed->skew->size and then the normal game play will be resumed with the adjusted values.
struct {
    const char *name;
    byte        minValue;
    byte        maxValue;
    byte        incValue;
    byte        activeValue;
} params[] = {
    {"Position", 0,  0,  2,  0},   // paddle position
    {"Sound",    0,  1,  1,  1},   // game sound
    {"Speed",    1, 19,  1,  4},   // ball speed
    {"Skew",     1, 15,  1,  1},   // ball skew
    {"Size",    10, 45,  5, 25}    // paddle size
};

const byte numParams = sizeof(params) / sizeof(params[0]);
const byte speakerPin = A3;

int screenWidth;              // LCD display's width in pixels
int screenHeight;             // LCD display's height in pixels
int bx, by, br;               // ball's center coordinate (x,y) and its radius respectively
byte px, py;                  // x and y coordinates of paddle's the top left corner
byte allowSound;              // enables or disables sound
int xinc;                     // ball increment in x-direction
int yinc;                     // ball increment in y-direction
byte skew;                    // current skew value
byte pHeight;                 // paddle size (i.e. height in pixels)
const byte pWidth = 6;        // paddle width (in pixels)
unsigned int gameScore = 0;   // tracks the score
const int Pot = A0;

char strBuf[16];              // used for string formatting

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_FAST); // for 1306 I2C (128x64)

void setup()
{

  // Acquire the display size and dump it out.
  screenWidth  = u8g.getWidth();
  screenHeight = u8g.getHeight();
    
  // Clear the screen
  u8g.firstPage(); 
  do {} 
     while(u8g.nextPage());
   
  // These variables will hold the currently-set parameter values.
  allowSound = params[SOUND].activeValue; // sets sound on/off
  xinc = params[SPEED].activeValue;       // defines the speed
  skew = params[SKEW].activeValue;        // defines the skew
  pHeight = params[SIZE].activeValue;     // defines paddle size

  // Setup paddle parameters (refers to the top left corner of the paddle)
  params[POSITION].minValue = 0;
  params[POSITION].maxValue = screenHeight - pHeight;
  params[POSITION].activeValue = (params[POSITION].maxValue - params[POSITION].minValue) / 2; // Center the paddle position
    
  // Initialize the RE's settings, based on the default parameter values.

/*      _ _
      /     \
     |   *   |  [bx,by] is the coordinate of the ball's center
      \ _ _ /
   
         |<->|   br is the ball's radius
*/

  // Configure starting parameters
  randomSeed(analogRead(1));
  br = 2;
  bx = br;
  by = random(br, screenHeight - br);
  yinc = random(-skew, skew);
  px = 0.7 * screenWidth;
  py = params[POSITION].maxValue - params[POSITION].activeValue;

  pinMode(speakerPin, OUTPUT);
  pinMode(Pot, INPUT);

  // Set up the gfx font
  u8g.setFont(u8g_font_profont10r);

}


void playSound(int frequency, int duration)
{
  if (allowSound)
  {
    tone(speakerPin, frequency, duration);
  }
}

void wallSound()
{
  playSound(4000, 50);
}

void paddleSound()
{
  playSound(2000, 50);
}

void scoreSound()
{
  int del = 300, hiFreq = 1250, loFreq = 200;

  for (int i = 0; i < 2; i++)
  {
    playSound(hiFreq, 450);
    delay(del);
    playSound(loFreq, 450);
    delay(del);
  }
}


void loop()
{
  static int frameCount = 0;
  boolean lostPoint = false;
      

  // Determine the paddle location
  py = params[POSITION].maxValue - round((analogRead(Pot)/1023.0)*params[POSITION].maxValue);
    
  // If the ball reached the left wall, reverse its direction
  if (xinc <= 0 && bx <= br)
  {
    xinc *= -1;
    wallSound();
  }

  // See if the ball hit the paddle...
  if((xinc > 0) && (bx+br >= px) && (by+br >= py) && (by <= py+pHeight+br) && (bx-br <= px+pWidth))
  {
    // Reverse its x-direction
    xinc *= -1;

    // Reverse its y-direction, depending on where the ball touched the paddle.
    // The top 3/7 of the paddle bounces the ball in one direction and the bottom 3/7 of the paddle 
    // bounces it in the opposite direction (with some randomness thrown in, as a function of skew). 
    if (by <= py + (3 * pHeight) / 7)
      yinc = -random(1, skew + 1); // Add some randomness to the ball motion, based on the current skew setting
    if (by >= py + (4 * pHeight) / 7)
      yinc = random(1, skew + 1);  // Add some randomness to the ball motion, based on the current skew setting

    gameScore++;
    paddleSound();
  }

  // Check if the ball is clear of the top and bottom walls
  if (by+yinc >= (screenHeight-br) ||   // is the ball above the bottom wall, or
     (by+yinc <= br))                   // is the ball below the top wall
  {
    // ...bounce it off the wall
    yinc *= -1;
    wallSound();
  }

  // See if the ball missed the paddle and reached the right side.
  // If so, update score and relaunch it from the left side.
  if (bx >= screenWidth)
  {
    xinc = params[SPEED].activeValue;
    yinc = random(-skew, skew);
    bx = px - ((px / xinc) *  xinc);
    by = random(br, screenHeight-br);

      lostPoint = true;
      Serial.println("Lost Point - incremented gameScore.");

    gameScore = 0;
  }
  else
  {
    // Advance the ball in the horizontal and vertical directions
    bx += xinc;
    by += yinc;
  }
      
  u8g.firstPage();
  do {
    if (lostPoint == false)
    {
      // Draw normal screens: regular play or adjust screens
        // Check the Adjust Mode on alternate frames; this gives better performance
      // Draw the borders
      u8g.drawLine(0, 0, screenWidth-1, 0);
      u8g.drawLine(0, 0, 0, screenHeight-1);
      u8g.drawLine(0, screenHeight-1, screenWidth-1, screenHeight-1);

        u8g.drawDisc(bx, by, br, U8G_DRAW_ALL);   // Draw the ball as a disc (i.e. solid circle)
        u8g.drawRBox(px, py, pWidth, pHeight, 2); // Draw paddle as solid box; use rounded corners with a radius of 2

      sprintf(strBuf, "%d", gameScore);
      u8g.drawStr((px+pWidth+screenWidth-u8g.getStrPixelWidth(strBuf))/2, screenHeight/2, strBuf);
    }
    else
    {
      // Display the "You Lose" screen
      u8g.setFont(u8g_font_gdb20r); // switch to bigger font
      strcpy (strBuf, "TRY");
      u8g.drawStr((screenWidth-u8g.getStrPixelWidth(strBuf))/2, screenHeight/2, strBuf);
      strcpy (strBuf, "AGAIN!");
      u8g.drawStr((screenWidth-u8g.getStrPixelWidth(strBuf))/2, screenHeight, strBuf);
      u8g.setFont(u8g_font_profont10r); // switch back to our normal font
     }
  } while (u8g.nextPage());

  if (lostPoint == true)
  {
    // Play annoying sound and let the user see the "You Lose" screen.
    scoreSound();
    delay(200);
  }
}
