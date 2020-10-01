#include "fxBargraph.h"

fxBargraphDot::fxBargraphDot(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr, bool rtl)
  : fxBargraph(lcd, x, y, id, width, max, clr, rtl) {
    steps = CHAR_COLS + 1; // bridge inter-character gap
    fullchar = id+1;
    setLinePattern(0b11011011);
}

void fxBargraphDot::createFraction(byte frac) {
  // Create fractional custom character
  byte pattern;
  if (rtl) pattern = (0b11111100 << frac) >> 8;
  else pattern = 0b11111000000 >> frac;

  pattern = pattern & 0b00011011;

  byte dyn[CHAR_ROWS] = { 0,0,0,0,0,0,0,0 };

  for (byte r=0; r<CHAR_ROWS; r++)
    dyn[r] =  (bitRead(mask, r) == 1) ? pattern : 0;
   
  lcd.createChar(id, dyn);
}

void fxBargraphDot::setLinePattern(byte mask) {
  byte pattern = 0b00011011;

  byte dyn[CHAR_ROWS];
  for (byte row=0; row<CHAR_ROWS; row++)
    dyn[row] =  (bitRead(mask, row) == 1) ? pattern : 0;
    
  lcd.createChar(fullchar, dyn);

  this->mask = mask;
}

