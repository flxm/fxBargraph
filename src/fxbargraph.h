#pragma once

#include <arduino.h>
#include <LiquidCrystal_I2C.h>

#define CHAR_COLS 5
#define CHAR_ROWS 8

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
    LiquidCrystal_I2C& lcd;

    int val;
    int maxval;
    int lastval;

    byte id;
    byte x;
    byte y;
    byte width;
 
    byte clr;
    byte fullchar;
    byte lastnum;
    byte steps;

    bool rtl;
};


class fxBargraphFine : public fxBargraph {
  public:
    fxBargraphFine(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr=' ', bool rtl=false);
   
  protected:
    virtual void createFraction(byte frac);
};


class fxBargraphHighres : public fxBargraph {
  public:
    fxBargraphHighres(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr=' ');
   
  protected:
    virtual void createFraction(byte frac);
};

class fxBargraphThin : public fxBargraph {
  public:
    fxBargraphThin(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr=' ', bool rtl=false);
   
  protected:
    virtual void createFraction(byte frac);
};

/**
 * Requires 2 custom characters!
 */
class fxBargraphLine : public fxBargraph {
  public:
    fxBargraphLine(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr=' ', bool rtl=false);
   
    virtual void setLineWidth(byte width);

    virtual void setLinePattern(byte mask);

  protected:
    virtual void createFraction(byte frac);

    byte mask;
};

/**
 * Requires 2 custom characters!
 */
class fxBargraphDot : public fxBargraph {
  public:
    fxBargraphDot(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr=' ', bool rtl=false);

  protected:
    virtual void setLinePattern(byte mask);
  
    virtual void createFraction(byte frac);

    byte mask;
};

/**
 * Requires 2 custom characters!
 */
class fxBargraphStriped : public fxBargraph {
  public:
    fxBargraphStriped(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr=' ', bool rtl=false);

  protected:
    virtual void setLinePattern(byte mask);
      
    virtual void createFraction(byte frac);
};

/**
 * 
 */
class fxBargraphVertical : public fxBargraph {
  public:
    fxBargraphVertical(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max);

  protected:
    virtual void createFraction(byte frac);
};


