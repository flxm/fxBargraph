#include "fxBargraph.h"

fxBargraph::fxBargraph(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr, bool rtl)
  : lcd(lcd), val(0), x(x), y(y), id(id), width(width), maxval(max), clr(clr), rtl(rtl) {
  lastval = -1;
  lastnum = width;
  steps = 1;
  fullchar = 255;
}

void fxBargraph::setValue(int newval) {
  newval = constrain(newval, 0, maxval);

  if (newval == lastval) return;
  
  val = newval;
  draw();
}

void fxBargraph::createFraction(byte frac) { }

void fxBargraph::draw() {
  int normalized = (((long)steps*width) * val / maxval );
  byte num =  normalized / steps;
  byte frac = normalized % steps;

  if (frac > 0) createFraction(frac);
  
  if (rtl) lcd.rightToLeft();

  // Draw full bars
  if (num > lastnum) {
    byte start = x + (rtl ? width - lastnum -1 : lastnum);
    lcd.setCursor(start, y);
    for (byte i=lastnum; i<num; i++)
      lcd.printByte(fullchar);
  }

  // Draw fraction
  if (num < width) {
    byte start = x + (rtl ? width - num -1 : num);
    lcd.setCursor(start, y); // needed for lcd ram switch
    if (frac > 0) lcd.printByte(id);

  // Clear remaining space
    if (num <= lastnum) {
      for (byte i=num+(frac==0?0:1); i<min(lastnum+1, width); i++)
        lcd.printByte(clr);
    }
  }

  if (rtl) lcd.leftToRight();
  
  lastval = val;
  lastnum = num;
}

