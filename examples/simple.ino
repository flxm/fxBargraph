#include <LiquidCrystal_I2C.h>
#include <fxbargraph.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// display,x,y,id,width,maxvalue
fxBargraph bar(lcd, 0, 0, 0, 16, 1023);

void setup() {
  pinMode(A0, INPUT);
  lcd.init();
}

void loop() {
  bar.setValue( analogRead(A0) );
}
