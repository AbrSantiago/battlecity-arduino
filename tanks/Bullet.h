#ifndef BULLET_H
#define BULLET_H

#include <Adafruit_SH110X.h>

class Tank;

class Bullet {
public:
  int x, y, dir;
  // bool outOfLimit = false;
  Bullet(int x, int y, int dir);
  void move();
  // bool checkCollision(Tank& tank);
};

#endif  // BULLET_H