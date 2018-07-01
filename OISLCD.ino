// include the library code:
#include <LiquidCrystal.h>
#include <ArduinosInSpace.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
ObjectsInSpace OIS(Serial, 4);

void setup() 
{
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2); //specific for a 16x2 LCD screen (change this for different sizes)

  Serial.begin(9600); //must be 9600
  OIS.begin(); //begin the handshake/syncronisation with the game

  //handshake
  OIS.registerFloat(CURRENT_SPEED, speedCallback); //register the command to get the speed from the game. check below for the callback
  OIS.registerInt(DIRECTION, headingCallback);
  OIS.registerInt(POWER_LEVEL, powerCallback);
  OIS.registerBool(MAIN_ENGINE_BURNING, burningCallback);

  OIS.activate(); //stop syncing and ACTIVATE
}

void loop() 
{
  OIS.update(); //required to keep getting info from the game.
}

void speedCallback(int channel, float data)//because we registered this in setup(), this gets called every time OIS.update() is called. therefore our info is refreshed
{                               //^ we registered a float so this needs to be a float
  lcd.setCursor(0,0); //set the cursor to the top left of the screen (0,0)
  lcd.print("SPD:"); //print something to the screen! this automatically moves the cursor
  lcd.print(data); //so we dont need to move it again before the next printout
}

void headingCallback(int channel, int data)//same as above but for an int
{                                 
  lcd.setCursor(0, 1); //set the cursor to the second row
  lcd.print("HDG:");
  lcd.print(data);
}

void powerCallback(int channel, int data)
{
  lcd.setCursor(8, 0); //set the cursor to the 9th position of the first row
  lcd.print("PWR:");
  lcd.print(data);
}

void burningCallback(int channel, bool data)
{
  lcd.setCursor(15, 0);
  if(data == true)
  {
    lcd.print("#");
  }
  else
  {
    lcd.print(".");
  }
}

