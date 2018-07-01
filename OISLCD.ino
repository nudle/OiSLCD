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

