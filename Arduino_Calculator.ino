#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <BigNumber.h>
#include "header.h"
#include <Wire.h>

Keypad keypad = Keypad(makeKeymap(keysPad), rowPins, colPins, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

#include "functions.h"

void setup()
{
  
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  BigNumber::begin();
  BigNumber::setScale(15);
  lcd.init();
  lcd.backlight();
  openingAnimation();
  playMelody();
  lcd.blink();
}

void loop()
{
  unsigned int iter = 0;
  unsigned int operationIter = 0;
  unsigned int equalIter = 0;
  char operation;
  char keys;
  lcd.setCursor(0, 0);
  while (true)
  {
    if (iter < maxNum)
    {
      keys = myKeys();
      lcd.blink();
      lcd.setCursor(iter, 0);
      if (keys == 'C')
      {
        clearData(myNum, true, &iter, &operationIter, &equalIter);
      }
      else if (OPERATIONKEYS && !operationFlag2)
      {
        if (resultFlag)
        {
          clearRow(1);
          lcd.setCursor(0, 0);
          iter = 4;
          for (unsigned int i = 0; i < iter; i++)
          {
            myNum[i] = 0;
          }
          lcd.print("Ans");
          lcd.print(keys);
          ansFlag = true;
          operationIter = iter;
          operation = keys;
        }
        else if (operation != keys && operationFlag)
        {
          operation = keys;
          lcd.setCursor(iter - 1, 0);
          lcd.print(keys);
        }
        else if(operation == keys && operationFlag)
        {
          // Do Nothing
        }
        else
        {
          operation = keys;
          operationIter = iter;
          lcd.print(keys);
          iter++;
        }
        operationFlag = true;
        resultFlag = false;
        beepOnce(BUZZ_DEFAULT);
      }
      else if (keys == '=')
      {
        equalIter = iter;
        equalFlag = true;
        lcd.print(keys);
        beepOnce(BUZZ_EQUAL);
      }
      else
      {
        if ((isdigit(keys) && (iter < maxNum)))
        {
          if (resultFlag)
          {
            clearRow(1);
            lcd.setCursor(0, 0);
            resultFlag = false;
          }
          myNum[iter] = keys - '0';
          lcd.print(keys);
          iter++;
          if (operationFlag)
          {
            operationFlag2 = true;
          }
          beepOnce(BUZZ_DEFAULT);
        }else
        {
          lcd.setCursor(0, 1);
          lcd.print("1 operation only");
          beepOnce(BUZZ_ERROR);
        }
      }
    }
    else
    {
      clearRow(2);
      lcd.setCursor(0, 1);
      lcd.print("Max!  = or C");
      beepOnce(BUZZ_ERROR);
      while (true)
      {
        keys = myKeys();
        if (keys == 'C')
        {
          clearData(myNum, true, &iter, &operationIter, &equalIter);
          break;
        }
        else if (keys == '=')
        {
          clearRow(2);
          equalIter = iter;
          equalFlag = true;
          beepOnce(BUZZ_EQUAL);
          break;
        }
      }
    }
    if (equalFlag == true){
      break;
    }
  }

  if (operationFlag && !ansFlag)
  {
    num1 = finalNumber(myNum, 0, operationIter);
    num2 = finalNumber(myNum, operationIter + 1, equalIter);
    operationFlag = false;
  }
  else if (operationFlag && ansFlag)
  {
    num1 = result;
    num2 = finalNumber(myNum, operationIter, equalIter);
    operationFlag = false;
  }
  else
  {
    clearRow(1);
    lcd.setCursor(0, 0);
    num1 = finalNumber(myNum, 0, equalIter);
    lcd.print('=');
    result = num1;
    operation = '\0';
  }
  resultFlag = true;
  ansFlag = false;
  operationFlag2 = false;
  equalFlag = false;
  switch (operation)
  {
  case ('+'):
    result = num1 + num2;
    break;
  case ('-'):
    result = num1 - num2;
    break;
  case ('*'):
    result = num1 * num2;
    break;
  case ('/'):
    result = num1 / num2;

    if(num2 == 0)
      zeroFlag = true;
    break;
  default:
    break;
  }
  clearRow(2);
  lcd.setCursor(0, 1);
  lcd.noBlink();
  if(zeroFlag)
  {
    bigError("Cant Divide by 0!");
    clearData(myNum, true, &iter, &operationIter, &equalIter);
  }else{
    if(result > MAX_DISPLAY){
      bigError("Overflow Error!");
      clearData(myNum, true, &iter, &operationIter, &equalIter);
    }else
    {
      printBignum(result);
      clearArray(myNum);
    }
  }
}
