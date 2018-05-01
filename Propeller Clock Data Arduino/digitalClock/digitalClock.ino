#include <Wire.h>
#include <Rtc_Pcf8563.h>

Rtc_Pcf8563 rtc; 
int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
int delayVar = 400;
const byte BUTTON = 2;
volatile int r=0;

// interrupt handler...
void pinChange ()
{
  r=1;
}

void setup() {
  
  
  pinMode(latchPin, OUTPUT);
  digitalWrite (BUTTON,HIGH);  
  attachInterrupt (0, pinChange,RISING);
  
  rtc.initClock();
  //set a time to start with.
  //day, weekday, month, century, year
  rtc.setDate(20, 6, 1, 0, 14);
  //hr, min, sec
  rtc.setTime(8, 35, 40);
  
//Serial.begin(9600);
}

void loop() {
 
 if(r==1){ 
numWrite(12);
numWrite(12);
second();
numWrite(11);
minute();
numWrite(11);
hour();
delay(14);
day();
numIWrite(11);
month();
numIWrite(11);
year();
}
r=0;
rtc.formatTime();
rtc.formatDate();
  }


void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
 
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else {	
      pinState= 0;
    }
    
    digitalWrite(myDataPin, pinState);
    digitalWrite(myClockPin, 1);
    digitalWrite(myDataPin, 0);
  }
  digitalWrite(myClockPin, 0);
}

// Function to write numbers
void numWrite(int alp)
{
int AL=alp;
switch(AL)
{
case 1:
ledWrite(0);
delayMicroseconds(delayVar);
ledWrite(128);
delayMicroseconds(delayVar);
ledWrite(254);
delayMicroseconds(delayVar);
ledWrite(132);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 2:
ledWrite(140);
delayMicroseconds(delayVar);       
ledWrite(146);
delayMicroseconds(delayVar);
ledWrite(146);
delayMicroseconds(delayVar);
ledWrite(146);
delayMicroseconds(delayVar);
ledWrite(98);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 3:
ledWrite(198);
delayMicroseconds(delayVar);       
ledWrite(170);
delayMicroseconds(delayVar);
ledWrite(146);
delayMicroseconds(delayVar);
ledWrite(130);
delayMicroseconds(delayVar);
ledWrite(130);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 4:
ledWrite(254);
delayMicroseconds(delayVar);       
ledWrite(16);
delayMicroseconds(delayVar);
ledWrite(16);
delayMicroseconds(delayVar);
ledWrite(16);
delayMicroseconds(delayVar);
ledWrite(30);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 5:
ledWrite(98);
delayMicroseconds(delayVar);       
ledWrite(146);
delayMicroseconds(delayVar);
ledWrite(146);
delayMicroseconds(delayVar);
ledWrite(146);
delayMicroseconds(delayVar);
ledWrite(140);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 6: 
ledWrite(98);
delayMicroseconds(delayVar);       
ledWrite(146);
delayMicroseconds(delayVar);
ledWrite(146);
delayMicroseconds(delayVar);
ledWrite(146);
delayMicroseconds(delayVar);
ledWrite(124);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 7: 
ledWrite(16);
delayMicroseconds(delayVar);       
ledWrite(254);
delayMicroseconds(delayVar);
ledWrite(18);
delayMicroseconds(delayVar);
ledWrite(2);
delayMicroseconds(delayVar);
ledWrite(2);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 8: 
ledWrite(108);
delayMicroseconds(delayVar);       
ledWrite(146);
delayMicroseconds(delayVar);
ledWrite(146);
delayMicroseconds(delayVar);
ledWrite(146);
delayMicroseconds(delayVar);
ledWrite(108);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 9: 
ledWrite(124);
delayMicroseconds(delayVar);       
ledWrite(146);
delayMicroseconds(delayVar);
ledWrite(146);
delayMicroseconds(delayVar);
ledWrite(146);
delayMicroseconds(delayVar);
ledWrite(140);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 0: 
 
ledWrite(124);
delayMicroseconds(delayVar);       
ledWrite(130);
delayMicroseconds(delayVar);
ledWrite(130);
delayMicroseconds(delayVar);
ledWrite(130);
delayMicroseconds(delayVar);
ledWrite(124);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 11:
ledWrite(0);
  delayMicroseconds(delayVar);
 ledWrite(108);
 delayMicroseconds(delayVar);
 ledWrite(0);
 delay(2);
break;

default:
ledWrite(0);
delayMicroseconds(delayVar);
break;

}}

void ledWrite(int var)
{
int data = var;
digitalWrite(latchPin, 0);
   
    shiftOut(dataPin, clockPin,data); 
    
   shiftOut(dataPin, clockPin,0);
   
    digitalWrite(latchPin,1);

}

void second()
{
  int sec= rtc.getSecond();
  int sec1 = sec/10;
  int sec2 = sec%10;
  numWrite(sec2);
  numWrite(sec1);    
}

void minute()
{
  int minn= rtc.getMinute();
  int min1 = minn/10;
  int min2 = minn%10;
  numWrite(min2);
  numWrite(min1);    
}

void hour()
{
  int hor= rtc.getHour();
  int hor1 = hor/10;
  int hor2 = hor%10;
  numWrite(hor2);
  numWrite(hor1);    
}


void numIWrite(int alp)
{
int AL=alp;
switch(AL)
{
case 1:
//int b[]={9,31,1};
ledWrite(9);
delayMicroseconds(delayVar);
ledWrite(31);
delayMicroseconds(delayVar);
ledWrite(1);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 2:
ledWrite(23);
delayMicroseconds(delayVar);
ledWrite(21);
delayMicroseconds(delayVar);
ledWrite(29);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 3:
ledWrite(17);
delayMicroseconds(delayVar);
ledWrite(21);
delayMicroseconds(delayVar);
ledWrite(31);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 4:
ledWrite(28);
delayMicroseconds(delayVar);
ledWrite(4);
delayMicroseconds(delayVar);
ledWrite(31);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 5:
ledWrite(29);
delayMicroseconds(delayVar);
ledWrite(21);
delayMicroseconds(delayVar);
ledWrite(23);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 6:
ledWrite(31);
delayMicroseconds(delayVar);
ledWrite(21);
delayMicroseconds(delayVar);
ledWrite(23);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 7:
ledWrite(16);
delayMicroseconds(delayVar);
ledWrite(16);
delayMicroseconds(delayVar);
ledWrite(31);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 8:
ledWrite(31);
delayMicroseconds(delayVar);
ledWrite(21);
delayMicroseconds(delayVar);
ledWrite(31);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 9:
ledWrite(29);
delayMicroseconds(delayVar);
ledWrite(21);
delayMicroseconds(delayVar);
ledWrite(31);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 0:
ledWrite(31);
delayMicroseconds(delayVar);
ledWrite(17);
delayMicroseconds(delayVar);
ledWrite(31);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;

case 11:
ledWrite(4);
delayMicroseconds(delayVar);
ledWrite(4);
delayMicroseconds(delayVar);
ledWrite(0);
delayMicroseconds(delayVar);
break;


default:
ledWrite(0);
delayMicroseconds(delayVar);
break;

}}

void month()
{
  int k = rtc.getMonth();
  int k1=k/10;
  numIWrite(k1);
  k1 = k%10;
  numIWrite(k1);
}
void day()
{
  int k= rtc.getDay();
  int k1=k/10;
  numIWrite(k1);
  k1 = k%10;
  numIWrite(k1);
}

void year()
{
  numIWrite(2);
  numIWrite(0);
int k =rtc.getYear();
 k =k%2000;
int k1 = k/10;
numIWrite(k1);
k1= k%10;
numIWrite(k1);

}



