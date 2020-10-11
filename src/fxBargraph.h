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

/**
 * @brief Baseclass for standard bargraph rendering.
 *        Resolution on character level.
 *        No custom character required.
 */
class fxBargraph {
  public:
    /**
     * @brief Constructor
     *
     * @param lcd Reference to lcd display instance
     * @param x Starting column (0-based)
     * @param y Row ro render (0-based)
     * @param id Unique value (0...7), 
     * @param width Length of the bar in characters
     * @param max Maximum value for normalization
     * @param clr character to be used for empty fields
     * @param rtl true for right to left rendering
     */
    fxBargraph(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr=' ', bool rtl=false);

    /**
     * @brief Sets the bargraph value and rerenders it
     *
     * @param newval New value
     * 
     * @returns true if visible graph has changed
     */
    virtual bool setValue(int newval);

  protected:
    /**
     * @brief Renders the bargraoh
     * 
     * @returns true if visible graph has changed
     */
    virtual bool draw();

    /**
     * @brief Creates the custom character for intra-character resolution
     */
    virtual void createFraction(byte frac);

  protected:
    LiquidCrystal_I2C& lcd; ///< Reference to LC display instance

    int val; ///< Current bargraph value
    int maxval; ///< Maximum value at 100%
    int lastval; ///< Value at last update

    byte id; ///< Bargraph id; corresponds to custom character index used fror fractional part
    byte x; ///< Starting x position
    byte y; ///< Starting y position
    byte width; ///< Number of character to occupy
 
    byte clr; ///< Character used for rendering clear space
    byte fullchar; ///< Character used for rendering full elements
    byte lastnum; ///< Last number of full 
    byte lastfrac; ///< Last fractional value

    byte steps; ///< Step resolution for fractional characters
    bool rtl; ///< Right2left support active
};


/**
 * @brief Derived class for rendering fraction 
 */
class fxBargraphFine : public fxBargraph {
  public:
    fxBargraphFine(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr=' ', bool rtl=false);
   
  protected:
    virtual void createFraction(byte frac);
};


/**
 * @brief Derived class for rendering fraction with highest resolution
 */
class fxBargraphHighres : public fxBargraph {
  public:
    fxBargraphHighres(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr=' ');
   
  protected:
    virtual void createFraction(byte frac);
};


/**
 * @brief Derived class for rendering single pixel wide bargraph
 */
class fxBargraphThin : public fxBargraph {
  public:
    fxBargraphThin(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr=' ', bool rtl=false);
   
  protected:
    virtual void createFraction(byte frac);
};


/**
 * @brief Derived class for bargraph with arbitrary thickness. Requires 2 custom characters!
 */
class fxBargraphLine : public fxBargraph {
  public:
    fxBargraphLine(LiquidCrystal_I2C& lcd, byte x, byte y, byte id, byte width, int max, byte clr=' ', bool rtl=false);

    /**
     * @brief Sets the line width (default: 1 pixel)
     *
     * @param width Vertical thickness (0...8 pixels)
     */
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


