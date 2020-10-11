#include "fxBargraph.h"

fxBargraphHighres::fxBargraphHighres(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr)
  : fxBargraph(lcd, x, y, id, width, max, clr) {
    steps = CHAR_COLS*CHAR_ROWS;
}

void fxBargraphHighres::createFraction(byte frac) {
  // Create fractional custom character
  byte dyn[CHAR_ROWS] = { 0,0,0,0,0,0,0,0 };
  for (int row=0; row<CHAR_ROWS; row++)
    for (int col=0; col<CHAR_COLS; col++) {
      if (rtl) dyn[row] += (frac > (row+col*CHAR_ROWS)) ? 0x01 << col : 0x00;
      else dyn[row] += (frac > (row+col*CHAR_ROWS)) ? 0x10 >> col : 0x00;
    }
  lcd.createChar(id, dyn);
}

