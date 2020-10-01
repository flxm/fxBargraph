#include "fxBargraph.h"

fxBargraphLine::fxBargraphLine(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr, bool rtl)
  : fxBargraph(lcd, x, y, id, width, max, clr, rtl) {
    steps = CHAR_COLS + 1; // bridge inter-character gap
    fullchar = id+1;
    setLineWidth(1);
}

void fxBargraphLine::createFraction(byte frac) {
  // Create fractional custom character
  byte pattern;
  if (rtl) pattern = (0b11111100 << frac) >> 8;
  else pattern = 0b11111000000 >> frac;

  byte dyn[CHAR_ROWS] = { 0,0,0,0,0,0,0,0 };

  for (byte r=0; r<CHAR_ROWS; r++)
    dyn[r] = (bitRead(mask, r) == 1) ? pattern : 0;
   
  lcd.createChar(id, dyn);
}

void fxBargraphLine::setLineWidth(byte width) {
  width = constrain(width, 0, CHAR_ROWS);
  mask = 0;
  
  for (byte w=1; w<=width; w++)
    bitSet(mask, w%2==0 ? 3+w/2 : 3-w/2);

  setLinePattern(mask);
}

void fxBargraphLine::setLinePattern(byte mask) {
  byte pattern = 0b00011111;

  byte dyn[CHAR_ROWS] = { 0,0,0,0,0,0,0,0 };
  for (byte row=0; row<CHAR_ROWS; row++)
    dyn[row] = (bitRead(mask, row) == 1) ? pattern : 0;
    
  lcd.createChar(fullchar, dyn);

  this->mask = mask;
}

