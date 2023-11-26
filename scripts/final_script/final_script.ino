#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h> 
#define RST_PIN 9         
#define SS_PIN 10      

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal lcd(8, 7, 5, 4, 3, 2);  
int Contrast = 75;
String correct_UID = "C925E914";

const int pin = 1;

void setup() {
	while (!Serial);		
  pinMode(pin, OUTPUT);
	SPI.begin();	
	mfrc522.PCD_Init();
	delay(4);
	mfrc522.PCD_DumpVersionToSerial();
  analogWrite(6, Contrast);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("ZAMKNIETE");
  lcd.setCursor(0, 1);
  lcd.print("ZBLIZ KARTE");
  delay(4);
  digitalWrite(pin, HIGH);
  delay(200);
}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print("ZAMKNIETE");
  lcd.setCursor(0, 1);
  lcd.print("ZBLIZ KARTE");
  delay(200);
  digitalWrite(pin, HIGH);
  delay(200);
	if ( ! mfrc522.PICC_IsNewCardPresent()) {
		return;
	}
	if ( ! mfrc522.PICC_ReadCardSerial()) {
		return;
	}
  String cardUID = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardUID += String(mfrc522.uid.uidByte[i], HEX);
  }
  cardUID.toUpperCase();
  if (correct_UID == cardUID)
  {
    delay(200);
    digitalWrite(pin, LOW);
    delay(200);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("OTWARTE");
    delay(5000);
    lcd.clear();
  }
  else
  {
    digitalWrite(pin, HIGH);
    delay(200);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("NIEPOPRAWNA");
    lcd.setCursor(0, 1);
    lcd.print("KARTA");
    delay(3000);
    lcd.clear();
  }
}