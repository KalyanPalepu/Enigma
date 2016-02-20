#include <LiquidCrystal.h>
#include <Wire.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char rotors[] = {'A', 'A', 'A'};


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  Wire.begin(8); 
  Wire.onReceive(receiveEvent);
  lcd.setCursor(0, 0);
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(rotors[2]);
  lcd.setCursor(8, 1);
  lcd.print(rotors[1]);
  lcd.setCursor(15, 1);
  lcd.print(rotors[0]);
  delay(100);
}

void receiveEvent(int howMany) {
  for(int i = 0; i < 3; i++){
    char c = Wire.read();
    rotors[i] = c;
  }
}
