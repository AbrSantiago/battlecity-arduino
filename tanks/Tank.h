#ifndef TANK_H
#define TANK_H

#include <Keypad.h>
#include <Adafruit_SH110X.h>

class Tank {
public:
  Tank(int startX, int startY, const unsigned char* tankBitmap, int startDir, Keypad* tankKeypad);
  void move();
  void draw();
  void shoot();

private:
  int x, y, dir;
  const unsigned char* bitmap;
  Keypad* keypad;
  void processMovement(int pressedKey);
};

#endif  // TANK_H