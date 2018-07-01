//www.elegoo.com
//2016.12.9

/*
  LiquidCrystal Library - Hello World

  Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
  library works with all LCD displays that are compatible with the
  Hitachi HD44780 driver. There are many of them out there, and you
  can usually tell them by the 16-pin interface.

  This sketch prints "Hello World!" to the LCD
  and shows the time.

  The circuit:
   LCD RS pin to digital pin 7
   LCD Enable pin to digital pin 8
   LCD D4 pin to digital pin 9
   LCD D5 pin to digital pin 10
   LCD D6 pin to digital pin 11
   LCD D7 pin to digital pin 12
   LCD R/W pin to ground
   LCD VSS pin to ground
   LCD VCC pin to 5V
   10K resistor:
   ends to +5V and ground
   wiper to LCD VO pin (pin 3)

  Library originally added 18 Apr 2008
  by David A. Mellis
  library modified 5 Jul 2009
  by Limor Fried (http://www.ladyada.net)
  example added 9 Jul 2009
  by Tom Igoe
  modified 22 Nov 2010
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/LiquidCrystal
*/

// include the library code:
#include <LiquidCrystal.h>
#include <ArduinosInSpace.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
ObjectsInSpace OIS(Serial, 4);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin(9600);
  OIS.begin();

  //handshake
  OIS.registerFloat(CURRENT_SPEED, speedCallback);
  OIS.registerInt(DIRECTION, headingCallback);
  OIS.registerInt(POWER_LEVEL, powerCallback);
  OIS.registerBool(MAIN_ENGINE_BURNING, burningCallback);

  OIS.activate();
  
  // Print a message to the LCD.
  //lcd.print("Hello, World!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //lcd.setCursor(0, 0);
  OIS.update();

}

void speedCallback(int channel, float data)
{
  lcd.setCursor(0,0);
  lcd.print("SPD:");
  lcd.print(data);
}

void headingCallback(int channel, int data)
{
  lcd.setCursor(0, 1);
  lcd.print("HDG:");
  lcd.print(data);
}

void powerCallback(int channel, int data)
{
  lcd.setCursor(8, 0);
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

