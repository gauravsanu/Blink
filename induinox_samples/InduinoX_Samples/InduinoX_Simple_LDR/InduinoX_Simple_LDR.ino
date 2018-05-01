#include <LiquidCrystal.h>
int val = 0; // A Variable to Store the Light Value from the LDR
LiquidCrystal lcd(8,9,10,11,12,13);
void setup()
{
  //Serial.begin(9600);// Start a Serial Connection
  lcd.begin(16, 2);
  lcd.print("Light Intensity:");
}

void loop()
{
  val = analogRead(A3);// Reads a 10-bit value corresponding to the voltage applied on analog input pin 3.
  lcd.setCursor(0, 1);
  // Prints the given string / value to the serial monitor
  lcd.println(val);// prints the value of the variable val to the serial monitor and moves the cursor to the next line (the ln part of println does this)
  delay(1000);
  //lcd.clear();
}
