#include <LiquidCrystal.h>
#include <Wire.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  lcd.begin(16, 2);
  lcd.noCursor();
  Wire.begin(8); 
  Wire.onReceive(receiveEvent);
}

void loop() {
  delay(100);
}

void receiveEvent(int howMany) {
  for(int i = 0; i < 3; i++) {
    char c = Wire.read();
    lcd.setCursor(i * 5, 1);
    lcd.print(c);
  }
}
