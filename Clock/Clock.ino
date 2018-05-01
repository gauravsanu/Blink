#include <Wire.h>
#include <LiquidCrystal.h> 

LiquidCrystal lcd(8,9,10,11,12,13);

const int backlight =13;
const int buttonHr = 7; //digital pin used as hour adjustment input
const int buttonMin = 8; //digital pin used as min adjustment input

int secs =0;
int secs2 = 0;
int mins = -1;
int hrs = 0;
boolean isAM = true; 

int milliDivSecs = 1000;
int milliDivMins = 60000;
int milliDivHrs = 360000;

unsigned long prevmillis=0;

int interval = 1000;


void setup(){
  pinMode(backlight, OUTPUT);
  pinMode(buttonHr, INPUT);
  pinMode(buttonMin, INPUT);
  
  digitalWrite(backlight, HIGH);
  lcd.begin(16,2); //set number of cols and rows
  
  //print out LCD clock duisplay
  lcd.setCursor(5,0);
  lcd.print("09:30:00 AM");
  
  //Serial.begin(9600);
}


void loop(){
   
  unsigned long currmillis = millis();

  //detect button pressing
  if(digitalRead(buttonHr) == HIGH){
    delay(25);
    hrs = hrs+1;
    updateHrs();
    
    //update AMPM on button press
    if(hrs==12){
      updateAMPM();
    }
    
    delay(400);
  }
  if(digitalRead(buttonMin) == HIGH){
    delay(25);
    mins = mins + 1;
    Serial.println(mins);
    updateMin();
    delay(400);
  }
  
  if(currmillis-prevmillis > 999){
    lcd.clear();
    prevmillis =currmillis;
    if(secs<10){
      lcd.setCursor(12,0);
      lcd.print(secs);
      lcd.setCursor(11,0);
      lcd.print(0);
    }
    else{
      lcd.setCursor(11,0);
      lcd.print(secs);
    }

    //display minutes
    if(secs == 0){
      mins = mins+1;
      updateMin();
    }
    

    //get new seconds from system time
    secs = (millis()/milliDivSecs)%60; // divide by 1000 and mod by 60 gives seconds from milliseconds  
    
  }

}
  
  //update min function 
  //calls the update am apm funciton and the update hours functions.
  void updateMin(){
      if(mins > 59){
        hrs = hrs+1;
        updateHrs();  //update hours then
        if(hrs==11 && mins >59){
          updateAMPM();
        }
        mins = 0;  //reset mins

        lcd.setCursor(8,0);
        lcd.print("00");
      }
      if(mins < 10){
        lcd.setCursor(9,0);
      }
      else{
        lcd.setCursor(8,0);
      }
      lcd.print(mins);
  }
  
  //update hour function
  void updateHrs(){
      //display hours - needs fixing for am pm

       if(hrs> 12){
        //reset to 1
        hrs = 1;
      }
      if(hrs< 10){
        lcd.setCursor(5,0);
        lcd.print(" ");
        lcd.setCursor(6,0);
      }
      else{
        lcd.setCursor(5,0);
      }
      lcd.print(hrs);
      
  }
  
  void updateAMPM(){
      if(isAM){
        isAM = false;
        lcd.setCursor(14,0);
        lcd.print("PM");
      }
      else{
        isAM = true;
        lcd.setCursor(14,0);
        lcd.print("AM");
      }
  }
