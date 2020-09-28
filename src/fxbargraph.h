#ifndef fxBargraph_h
#define fxBargraph_h

#include <arduino.h>
#include <LiquidCrystal_I2C.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

class fxBargraph {
  public:
    fxBargraph(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr=' ', bool rtl=false);

    virtual void setValue(int newval);

  protected:
    virtual void draw();

    virtual void createFraction(byte frac);

  protected:
    const LiquidCrystal_I2C& lcd;

    int val;
    int maxval;
    int lastval;

    byte id;
    byte x;
    byte y;
    byte width;
    byte clr;

    byte lastnum;
    byte steps;
    bool rtl;
    byte fullchar;
};
#endif
