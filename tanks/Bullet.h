#ifndef BULLET_H
#define BULLET_H

#include <Adafruit_SH110X.h>

class Bullet {
public:
  int x, y, dir;
  const unsigned char* bitmap;
  bool inUse = false;
  Bullet(int x, int y, int dir, const unsigned char* bulletBitmap);
  void move();
  void draw();  
};

#endif  // BULLET_H