#ifndef TANK_H
#define TANK_H

#include <Keypad.h>
#include <Adafruit_SH110X.h>

class Tank {
public:
  Tank(int startX, int startY, const unsigned char* tankBitmap, Keypad* tankKeypad);
  void move();
  void draw();

private:
  int x, y;
  const unsigned char* bitmap;
  Keypad* keypad;
  void processMovement(int pressedKey);
};

#endif  // TANK_H