const int buzzer = 6; //buzzer to arduino pin 9


void setup(){
 
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output

}

void loop(){
  playBuzzer( 5 );
}

void playBuzzer( int numberofTimes ){
  for(int b = 1; b <= numberofTimes; b ++ ) {
    tone(buzzer, 400); // Send 1KHz sound signal...
    delay(500);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(500);        // ...for 1sec
  }
}
