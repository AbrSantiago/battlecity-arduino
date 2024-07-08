#ifndef TANK_H
#define TANK_H

#include <Keypad.h>
#include <Adafruit_SH110X.h>
#include "Bullet.h"

class Bullet;

class Tank {
public:
  int x, y;
  Tank(int player_code, int startX, int startY, const unsigned char* tankBitmap, int startDir, Keypad* tankKeypad);
  void move();
  void draw();
  Bullet shoot();

private:
  int id, dir, numBullets;
  const unsigned char* bitmap;
  Keypad* keypad;
  void processMovement1(int pressedKey);
  void processMovement2(int pressedKey);
};

#endif  // TANK_H