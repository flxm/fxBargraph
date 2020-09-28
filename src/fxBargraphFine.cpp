#include "fxBargraph.h"

fxBargraphFine::fxBargraphFine(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr=' ', bool rtl=false)
  : fxBargraph(lcd, x, y, id, width, max, clr, rtl) {
    steps = CHAR_COLS + 1; // bridge inter-character gap
}

void fxBargraphFine::createFraction(byte frac) {
  // Create fractional custom character
  byte dyn[CHAR_ROWS];
  byte x;
  if (rtl) x = (0b11111100 << frac) >> 8;
  else x = 0b11111000000 >> frac;
  for (int row=0; row<CHAR_ROWS; row++)
      dyn[row] = x;
  lcd.createChar(id, dyn);
}

