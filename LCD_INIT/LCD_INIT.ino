#include <LiquidCrystal.h> 
int Contrast=75;
 LiquidCrystal lcd(8, 7, 5, 4, 3, 2);  

 void setup()
 {
    analogWrite(6,Contrast);
     lcd.begin(16, 2);
  } 
     void loop()
 { 
     lcd.setCursor(0, 0);
     lcd.print("ZAMKNIETE");
   
    lcd.setCursor(0, 1);
     lcd.print("ZBLIZ KARTE");
 }
