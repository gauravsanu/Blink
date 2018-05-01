/*  Induino R3 User Guide - Program 7.2 -  Remote Controlled Binary Counter using the IR remote library
 
 This sketch increases a 3 bit number every time the channel up key on a remote is pressed
 and decreases a 3 bit number every time the channel down key on a remote is pressed
 and shows the output on 3 LEDs   
 */
#include <IRremote.h>

int RECV_PIN = 15;

IRrecv irrecv(RECV_PIN);

decode_results results;

int i = 0; // the countervalue for the binary counter
void setup()  
{  
  pinMode(11,OUTPUT);   // declare LED pins as output pins  
  pinMode(12,OUTPUT);  
  pinMode(13,OUTPUT);  

  irrecv.enableIRIn(); // Start the receiver
}  
void loop()  
{  
  if (irrecv.decode(&results))   // check whether a signal was received and decoded
  {
     //digitalWrite(13,HIGH); digitalWrite(11,HIGH); digitalWrite(12,HIGH);  // write LSB  
    if(results.value == 0x90) // 0x90 is the Channel UP Button Value on the Sony Remote provided as part of the Induino R3 Learners Kit
    {
      if(i<7)        // if counter value is less than 7 or 3 bits  
        i++;        // increment counter value  
      else           
        i=0;        // reset counter to 0 
    }
    if(results.value == 0x890) // 0x890 is the Channel UP Button Value on the Sony Remote provided as part of the Induino R3 Learners Kit
    {
      if(i>0)        // if counter value is greater than 0 or 3 bits  
        i--;        // decrement counter value  
      else           
        i=7;        // reset counter to 7
    }

    int a=i%2;      // calculate LSB   
    int b=i/2 %2;     // calculate middle bit  
    int c=i/4 %2;     // calculate MSB   
    digitalWrite(11,a);  // write MSB  
    digitalWrite(12,b);  // write middle bit  
    digitalWrite(13,c);  // write LSB  
    delay(150);     // A remote press will normally generate 3 signal trains. This is to avoid reading duplicates
    irrecv.resume();
  }  
}  
