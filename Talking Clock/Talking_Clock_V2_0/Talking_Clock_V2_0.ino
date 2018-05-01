/*                Talking Clock - V2.0
                by LAGSILVA - 21.Out.2016
             (Arduino UNO-R3 & DFPlayer_Mini)
  --------------------------------------------------------
  Note: All MP3 files name must be numered as "nnnn.mp3"
      Ex: "0000.mp3", "0001.mp3", "0002.mp3", ...
*/

#include <SoftwareSerial.h>       //Library to support DFPlayer
#include <DFPlayer_Mini_Mp3.h>    //Library of DFPlayer (module to play MP3 files)
#include <TM1637Display.h>        //Library of TM1637 Display (4 digitis x 7 segments)
#include <Time.h>                 //Time Library

int ajustaModo = 7;               //Switch of Mode
int ajustaMinuto = 6;             //Switch of minutes
int ajustaHora = 5;               //Switch of the hours

int hora, minuto, modo, ultimoMinuto, ultimaHora, dezHora, uniHora;

// Module connection pins (Digital Pins)
#define CLK 10         //Arduino Conection on Pin #10 = CLK of Display Module
#define DIO 11         //Arduino Conection on Pin #11 = DIO of Display Module

TM1637Display display(CLK, DIO);

//
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D
//

uint8_t dataWithColon[] = {
  0b10111111, // 0
  0b10000110, // 1
  0b11011011, // 2
  0b11001111, // 3
  0b11100110, // 4
  0b11101101, // 5
  0b11111101, // 6
  0b10000111, // 7
  0b11111111, // 8
  0b11101111, // 9
  0b00000000, // 10
};


void setup()
{

  Serial.begin (9600);
  mp3_set_serial (Serial);          //Set serial for DFPlayer-mini mp3 module - Arduino ports Tx and Rx
  mp3_set_volume (24);              //Set the volume (30 max)

  display.setBrightness (0x0a);     //(0x0f) is the max brightness;

  pinMode(ajustaModo, INPUT_PULLUP);
  pinMode(ajustaMinuto, INPUT_PULLUP);
  pinMode(ajustaHora, INPUT_PULLUP);

  modo = 0;
  ultimoMinuto = -1;
  ultimaHora = -1;

  mp3_play (86);      // Play the mode of Adjust or Silence
  delay(3000);

}


void loop()
{
  hora = hour();
  minuto = minute();
  dezHora = hora / 10;
  uniHora = hora % 10;

  display.showNumberDec(dezHora, true, 1, 0);
  display.setSegments(dataWithColon + uniHora, 1, 1);
  display.showNumberDec(minuto, true, 2, 2);

  if (digitalRead(ajustaHora) == LOW) {     //Setup of hours
    ultimaHora = -1;
    adjustTime(3600);
    delay(200);
  }

  if (digitalRead(ajustaMinuto) == LOW) {   //Setup of Minutes
    ultimoMinuto = -1;
    adjustTime(60);
    delay(200);
  }

  if (digitalRead(ajustaModo) == LOW) {     //Setup of Mode
    modo += 1;
    modo = modo % 3;
    delay(200);

    if (modo == 0) {                    // Play mode Adjust or Silence
      mp3_play (86);
      delay(3000);
    }

    if (modo == 1) {                    // Play mode Minute
      ultimoMinuto = minuto;
      mp3_play (85);
      delay(2500);
    }

    if (modo == 2) {                    // Play the Hour
      ultimaHora = hora;
      mp3_play (84);
      delay(3000);
    }

  }

  switch (modo) {

    case 1:                             // Play the Minute

      if (minuto != ultimoMinuto) {
        ultimoMinuto = minuto;

        mp3_play (hora);
        delay(2000);
        mp3_play (minuto + 24);
        delay(2500);
      }

      break;


    case 2:                             // Play the Hour

      if (hora != ultimaHora && hora >= 8 && hora <= 20) {
        ultimaHora = hora;

        mp3_play (hora);
        delay(2000);
        mp3_play (minuto + 24);
        delay(2500);

        for (int k = 1; k <= hora % 12; k++) {      // Bell Ring & Cuckoo
          mp3_play (87);
          delay(2000);
        }
        if (hora == 12) {
          for (int k = 1; k <= 12; k++) {           // Bell Ring & Cuckoo for 12:00 hours
            mp3_play (87);
            delay(2000);
          }
        }
      }

      break;

  }

}

