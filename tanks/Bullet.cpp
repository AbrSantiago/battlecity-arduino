#include "Bullet.h"
#include <Arduino.h>

extern Adafruit_SH1106G display;

Bullet::Bullet(int startX, int startY, int dir)
  : x(startX), y(startY), dir(dir) {}

void Bullet::draw() {
  display.drawBitmap(x, y, WHITE)
}

void Bullet::update() {
  switch (dir) {
    case 0:
      y++;
      break;
    case 1:
      x++;
      break;
    case 2:
      y--;
      break;
    case 3:
      x--;
      break;
    default:
      break;
  }
}

void Bullet::impact()