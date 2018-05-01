#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>

// initialize LCD
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

LiquidCrystal lcd(8,9,10,11,12,13);

// initialize RTC
RTC_DS1307 RTC;

//January February March April May June July August September October November December

char months[][12] = {"No","January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
void setup() {
  // set up the LCD's number of columns and rows: 
  //Serial.begin(57600);
  Serial.begin(9600);
  lcd.begin(16, 2);
  Wire.begin();
  //RTC.adjust(DateTime(t4));
  RTC.begin();
  
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
}

void loop() {
  // set the cursor to column 0, line 0
  lcd.setCursor(0, 0);
  DateTime now = RTC.now();
  int mins = now.minute();
  int secs = now.second();
  int hr = now.hour();

  //Serial.print( hr ;Serial.print( " "  );Serial.print( mins ); Serial.print( " "  );Serial.print( secs );
  
  int flag = 1 ;
  if( hr >= 12 ) {
    int amPmHr = hr - 12;
    flag = 2;
    lcd.print(amPmHr);
    
  }
  else {
    lcd.print(hr);
  }
  lcd.print(":");
  if (mins<10)
  {
    lcd.print(0);
  }
  lcd.print(mins);
  lcd.print(":"); 
  if (secs<10)
  {
    lcd.print(0);
  }
  lcd.print(secs); 
  if(flag == 1 ) {
    lcd.print(" AM");
  }
  else if( flag == 2 ) {
    lcd.print(" PM");
  }
  lcd.setCursor(0, 1);
  lcd.print(now.day());
  lcd.print(" ");
  lcd.print(months[now.month()]);
  lcd.print(" ");
  lcd.print(now.year());
  delay(1000);
}
