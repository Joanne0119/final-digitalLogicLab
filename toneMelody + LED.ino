/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody
*/

#include "pitches.h"

#define ROW1 13
#define ROW2 12
#define ROW3 11
#define ROW4 10
#define ROW5 9
#define ROW6 8
#define ROW7 7
#define ROW8 6

#define COL1 5
#define COL2 4
#define COL3 3
#define COL4 A4
#define COL5 A3
#define COL6 A2
#define COL7 A1
#define COL8 A0
#define BUTTON 2

byte incomingByte;

const int row[] = {

  ROW1, ROW2, ROW3, ROW4, ROW5, ROW6, ROW7, ROW8};

const int col[] = {

  COL1,COL2, COL3, COL4, COL5, COL6, COL7, COL8};
  
byte scan[8][8] = {

{1,0,0,0,0,0,0,0},

{0,1,0,0,0,0,0,0},

{0,0,1,0,0,0,0,0},

{0,0,0,1,0,0,0,0},

{0,0,0,0,1,0,0,0},

{0,0,0,0,0,1,0,0},

{0,0,0,0,0,0,1,0},

{0,0,0,0,0,0,0,1}

};

byte heart[8][8] = {

  {1,1,1,1,1,1,1,1},
  
  {1,0,0,1,1,0,0,1},
  
  {0,0,0,0,0,0,0,0},
  
  {0,0,0,0,0,0,0,0},
  
  {0,0,0,0,0,0,0,0},
  
  {1,0,0,0,0,0,0,1},
  
  {1,1,0,0,0,0,1,1},
  
  {1,1,1,0,0,1,1,1}

};
byte x[8][8] = {

  {0,1,1,1,1,1,1,0},
  
  {1,0,1,1,1,1,0,1},
  
  {1,1,0,1,1,0,1,1},
  
  {1,1,1,0,0,1,1,1},
  
  {1,1,1,0,0,1,1,1},
  
  {1,1,0,1,1,0,1,1},
  
  {1,0,1,1,1,1,0,1},
  
  {0,1,1,1,1,1,1,0}
 };

byte previousState=1, presentState=1, patternNumber=0;

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int sound[] = {
  NOTE_G4, NOTE_E3, NOTE_E3, 
  NOTE_F3, NOTE_D3, NOTE_D3
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int melodyDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

int soundDurations[] = {
  4, 8, 8, 
  4, 8, 8
};

int melodylen[2] = {8, 6};

int play = 1;


const byte interruptPin = 2;

void blink() {
  play = 1 - play;
}


void showPattern(byte matrix[8][8]){

  for(byte i = 0; i < 8; i++){
  
    for(byte j = 0; j < 8; j++){
    
      digitalWrite(row[j], 1 - scan[i][j]);
      
      digitalWrite(col[j], 1 - matrix[i][j]);
  
    }
    
    for(byte j = 0; j < 8; j++){
    
      digitalWrite(row[j], HIGH);
      
      digitalWrite(col[j], LOW);
  
    }

  }

}

void setup() {
  // iterate over the notes of the melody:
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, FALLING );
  for (byte i = 0; i <= sizeof(row); i++) {
  
    pinMode(row[i], OUTPUT);
  
  }
  
  for (byte i = 0; i <= sizeof(col); i++) {
  
    pinMode(col[i], OUTPUT);
  
  }
  
    pinMode(2, INPUT_PULLUP);


  Serial.begin(9600);

for (byte i = 0; i <= sizeof(row); i++) { pinMode(row[i], OUTPUT); }

for (byte i = 0; i <= sizeof(col); i++) { pinMode(col[i], OUTPUT); }

pinMode(2, INPUT_PULLUP);

}





void loop() {

while(play == 1) {
    for (int thisNote = 0; thisNote < melodylen[0]; thisNote++) {
        
//          presentState = digitalRead(interruptPin);
//          if(presentState == 0 && previousState == 1){
//            patternNumber = 1 - patternNumber;
//          }
//           if(patternNumber == 0){
//            showPattern(x);
//           }else {
//              showPattern(heart);
//           }
//           delay(5);
//           previousState = presentState;
//          ////
      showPattern(x);
      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / melodyDurations[thisNote];
      tone(A5, melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(A5);
      if(play != 1){
        thisNote = melodylen[0];
//        break;
      }
    }
    Serial.println(play);
    Serial.println(patternNumber);
  }
  
  while(play == 0) {

    for (int thisNote = 0; thisNote < 6; thisNote++) {
//      presentState = digitalRead(interruptPin);
//      if(presentState == 0 && previousState == 1){
//        patternNumber = 1 - patternNumber;
//      }
//       if(patternNumber == 0){
//        showPattern(x);
//       }else {
//          showPattern(heart);
//       }
//       delay(5);
//       previousState = presentState;
//        ////
        showPattern(heart);
      // to calculate the note duration, take one second divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / soundDurations[thisNote];
      tone(A5, sound[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      // stop the tone playing:
      noTone(A5);
      if(play != 0){
        thisNote = melodylen[0];
//        break;
      }
        
    }
    Serial.println(play);
    Serial.println(patternNumber);
  }
}

////
