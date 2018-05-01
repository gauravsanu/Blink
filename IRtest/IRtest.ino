/*
 * IRremote: IRtest unittest
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 *
 * Note: to run these tests, edit IRremote/IRremote.h to add "#define TEST"
 * You must then recompile the library by removing IRremote.o and restarting
 * the arduino IDE.
 */

#include <IRremote.h>
#include <IRremoteInt.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(8,9,10,11,12,13);
// Dumps out the decode_results structure.
// Call this after IRrecv::decode()
// void * to work around compiler issue
//void dump(void *v) {
//  decode_results *results = (decode_results *)v
void dump(decode_results *results) {
  int count = results->rawlen;
  if (results->decode_type == UNKNOWN) {
    lcd.println("Could not decode message");
  } 
  else {
    if (results->decode_type == NEC) {
      lcd.print("Decoded NEC: ");
    } 
    else if (results->decode_type == SONY) {
      lcd.print("Decoded SONY: ");
    } 
    else if (results->decode_type == RC5) {
      lcd.print("Decoded RC5: ");
    } 
    else if (results->decode_type == RC6) {
      lcd.print("Decoded RC6: ");
    }
    lcd.print(results->value, HEX);
    lcd.print(" (");
    lcd.print(results->bits, DEC);
    lcd.println(" bits)");
  }
  lcd.print("Raw (");
  lcd.print(count, DEC);
  lcd.print("): ");

  for (int i = 0; i < count; i++) {
    if ((i % 2) == 1) {
      lcd.print(results->rawbuf[i]*USECPERTICK, DEC);
    } 
    else {
      lcd.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
    }
    lcd.print(" ");
  }
  lcd.println("");
}

IRrecv irrecv(0);
decode_results results;

class IRsendDummy : 
public IRsend
{
public:
  // For testing, just log the marks/spaces
#define SENDLOG_LEN 128
  int sendlog[SENDLOG_LEN];
  int sendlogcnt;
  IRsendDummy() : 
  IRsend() {
  }
  void reset() {
    sendlogcnt = 0;
  }
  void mark(int time) {
    sendlog[sendlogcnt] = time;
    if (sendlogcnt < SENDLOG_LEN) sendlogcnt++;
  }
  void space(int time) {
    sendlog[sendlogcnt] = -time;
    if (sendlogcnt < SENDLOG_LEN) sendlogcnt++;
  }
  // Copies the dummy buf into the interrupt buf
  void useDummyBuf() {
    int last = SPACE;
    irparams.rcvstate = STATE_STOP;
    irparams.rawlen = 1; // Skip the gap
    for (int i = 0 ; i < sendlogcnt; i++) {
      if (sendlog[i] < 0) {
        if (last == MARK) {
          // New space
          irparams.rawbuf[irparams.rawlen++] = (-sendlog[i] - MARK_EXCESS) / USECPERTICK;
          last = SPACE;
        } 
        else {
          // More space
          irparams.rawbuf[irparams.rawlen - 1] += -sendlog[i] / USECPERTICK;
        }
      } 
      else if (sendlog[i] > 0) {
        if (last == SPACE) {
          // New mark
          irparams.rawbuf[irparams.rawlen++] = (sendlog[i] + MARK_EXCESS) / USECPERTICK;
          last = MARK;
        } 
        else {
          // More mark
          irparams.rawbuf[irparams.rawlen - 1] += sendlog[i] / USECPERTICK;
        }
      }
    }
    if (irparams.rawlen % 2) {
      irparams.rawlen--; // Remove trailing space
    }
  }
};

IRsendDummy irsenddummy;

void verify(unsigned long val, int bits, int type) {
  irsenddummy.useDummyBuf();
  irrecv.decode(&results);
  lcd.print("Testing ");
  lcd.print(val, HEX);
  if (results.value == val && results.bits == bits && results.decode_type == type) {
    lcd.println(": OK");
  } 
  else {
    lcd.println(": Error");
    dump(&results);
  }
}  

void testNEC(unsigned long val, int bits) {
  irsenddummy.reset();
  irsenddummy.sendNEC(val, bits);
  verify(val, bits, NEC);
}
void testSony(unsigned long val, int bits) {
  irsenddummy.reset();
  irsenddummy.sendSony(val, bits);
  verify(val, bits, SONY);
}
void testRC5(unsigned long val, int bits) {
  irsenddummy.reset();
  irsenddummy.sendRC5(val, bits);
  verify(val, bits, RC5);
}
void testRC6(unsigned long val, int bits) {
  irsenddummy.reset();
  irsenddummy.sendRC6(val, bits);
  verify(val, bits, RC6);
}

void test() {
  lcd.println("NEC tests");
  testNEC(0x00000000, 32);
  testNEC(0xffffffff, 32);
  testNEC(0xaaaaaaaa, 32);
  testNEC(0x55555555, 32);
  testNEC(0x12345678, 32);
  lcd.println("Sony tests");
  testSony(0xfff, 12);
  testSony(0x000, 12);
  testSony(0xaaa, 12);
  testSony(0x555, 12);
  testSony(0x123, 12);
  lcd.println("RC5 tests");
  testRC5(0xfff, 12);
  testRC5(0x000, 12);
  testRC5(0xaaa, 12);
  testRC5(0x555, 12);
  testRC5(0x123, 12);
  lcd.println("RC6 tests");
  testRC6(0xfffff, 20);
  testRC6(0x00000, 20);
  testRC6(0xaaaaa, 20);
  testRC6(0x55555, 20);
  testRC6(0x12345, 20);
}

void setup()
{
  //Serial.begin(9600);
  lcd.begin(16, 2);
  test();
}

void loop() {
}
