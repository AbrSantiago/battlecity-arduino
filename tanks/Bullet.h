#ifndef BULLET_H
#define BULLET_H

#include <Adafruit_SH110X.h>

class Bullet {
public:
  Bullet(int startX, int startY, int dir);
  void draw();
  void update();
  void impact(int tankX, int tankY);
  bool onLimit;

private:
  int x, y, dir;
};

#endif  // BULLET_H