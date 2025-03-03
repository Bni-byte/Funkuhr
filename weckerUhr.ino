#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int stunde = 0;
int minute = 0;
char weckerStunde;
char weckerMinute;

void setup() {
    lcd.begin(16, 2);
    pinMode(13, INPUT);
    analogWrite(6, 100); //Display Helligkeit 85
    //lcd.setCursor(0, 1);
    //lcd.print("Sontag");
}

void loop() {
  lcd.setCursor(0, 0);
  //Uhrzeit
  if(minute > 59){
    minute = 0;
    stunde++;
  }
  if(stunde > 23){
    stunde = 0;
  }
  if(stunde < 10){
  lcd.print(0);
  }
  lcd.print(stunde);
  lcd.print(":");
  if(minute < 10){
    lcd.print(0);
  }
  lcd.print(minute);
  minute++;
  delay(1000);
  //lcd.clear();

  //Wecker
  if(stunde == 0 && minute > weckerMinute && minute < weckerMinute+5){   //ändern 
    tone(8, 349, 200);
  }
  if(digitalRead(13) == HIGH){    //funktioniert nicht
    weckerMinute++;
  }
}