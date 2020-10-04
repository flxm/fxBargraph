#include "fxBargraph.h"

fxBargraphVertical::fxBargraphVertical(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max)
  : fxBargraph(lcd, x, y, id, 1, max, ' ', false) {
    steps = CHAR_ROWS;
}

void fxBargraphVertical::createFraction(byte frac) {
  byte pattern = 0b00011111;
  byte dyn[CHAR_ROWS] = { 0,0,0,0,0,0,0,0 };
  for (byte row=0; row<frac; row++)
    dyn[CHAR_ROWS-row-1] = pattern;
    
  lcd.createChar(id, dyn);
}

