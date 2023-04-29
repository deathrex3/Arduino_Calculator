void beepOnce(int freq, int duration)
{
  tone(BUZZER_PIN, freq, duration);
}

void playMelody()
{
  // int noteSize = sizeof(melody) / melody[0];
  for (int thisNote = 0; thisNote < 8; thisNote++)
  {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER_PIN, melody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 0.8;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
}

char myKeys()
{
  char myKey;
  do{
    myKey = keypad.getKey();
  }while (myKey == NO_KEY);
  return myKey;
}

BigNumber finalNumber(BigNumber *myNum, unsigned int myIter1, unsigned int myIter2)
{
  BigNumber myTotal = 0;
  for (unsigned int i = myIter1; i < myIter2; i++)
  {
    myTotal *= 10;
    myTotal += myNum[i];
  }
  return myTotal;
}

void clearRow(byte row=1)
{
  if(row == 1)
  {
    lcd.setCursor(0, 0);
    for (int i = 0; i < 16; i++)
    {
      lcd.write(' ');
    }
  }else{
    lcd.setCursor(0, 1);
    for (int i = 0; i < 16; i++)
    {
      lcd.write(' ');
    }
  }
}

void clearArray(BigNumber *arr){
    for (int i = 0; i < maxNum; i++)
  {
    arr[i] = '\0';
  }
}

void clearData(BigNumber *arr, bool cls, unsigned int *iter1, unsigned int *iter2, unsigned int *iter3)
{
  operationFlag = false;
  operationFlag2 = false;
  equalFlag = false;
  resultFlag = false;
  ansFlag = false;
  zeroFlag = false;
  clearArray(arr);
  if(cls){
    lcd.clear();
    lcd.setCursor(0, 0);
  }
  *iter1 = 0;
  *iter2 = 0;
  *iter3 = 0;
  lcd.blink();
  num1 = 0;
  num2 = 0;
  result = 0;
  beepOnce(BUZZ_CLEAR);
}

void bigError(String msg){
  lcd.print(msg);
  beepOnce(BUZZ_ERROR);
  delay(1000);
  beepOnce(BUZZ_DEFAULT);
  clearRow(2);
  lcd.setCursor(0,1);
  lcd.print("Clearing Data");
  for(unsigned int i=0;i<3;i++){
    lcd.print('.');
    beepOnce(BUZZ_CLEAR);
    delay(600);
  }
}

void printBignum(BigNumber bigNumber)
{
  char *bigNumberStr = bigNumber.toString();
  lcd.print(bigNumberStr);
  free(bigNumberStr);
}

void openingAnimation(){
  lcd.setCursor(0,1);
  lcd.print("by FiddleDiddle!");
  lcd.setCursor(3,0);
  lcd.print("CALCULATOR");
  delay(3000);
  for (int i = 0; i < 16; i++) {   // slide the text to the right
    lcd.scrollDisplayRight();       // scroll the display to the left
    delay(150);                    // wait for 250 milliseconds
  }
  lcd.clear();
}
