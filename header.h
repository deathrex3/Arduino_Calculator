#include <BigNumber.h>
#include "pitches.h"

//Definitions------------------------------------------------------------------------------
#define OPERATIONKEYS (keys == '+' || keys == '-' || keys == '*' || keys == '/')
#define BUZZER_PIN (3)
#define BUZZ_DEFAULT 1000,200
#define BUZZ_ERROR 300,100
#define BUZZ_EQUAL 2000,200
#define BUZZ_CLEAR 2000,400

//Constants------------------------------------------------------------------------------
//Keypad
const byte ROWS = 4;
const byte COLS = 4;

//Global Variables------------------------------------------------------------------------------
//Keypad
char keysPad[ROWS][COLS] = {
    {'1', '2', '3', '+'},
    {'4', '5', '6', '-'},
    {'7', '8', '9', '*'},
    {'C', '0', '=', '/'}};

byte rowPins[ROWS] = {7, 6, 5, 4};
byte colPins[COLS] = {8, 9, 10, 11};
// Flags
bool equalFlag = false;
bool operationFlag = false;
bool operationFlag2 = false;
bool resultFlag = false;
bool ansFlag = false;
bool zeroFlag = false;
//Numbers
BigNumber num1 = 0;
BigNumber num2 = 0;
BigNumber result = 0;
BigNumber MAX_DISPLAY = "9999999999999999";
//BUZZER
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
  //NOTE_G4, NOTE_E3, NOTE_G4, NOTE_E3
}; // define the notes of the melody
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
  //3, 3, 2, 1
};

//Memory Array
const int maxNum = 16;
BigNumber myNum[maxNum];
int myOp[maxNum];
char display[17];
