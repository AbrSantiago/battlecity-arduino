#include "Bullet.h"
#include <Arduino.h>

extern Adafruit_SH1106G display;

Bullet::Bullet(int startX, int startY, int dir)
  : x(startX), y(startY), dir(dir), onLimit(false) {}

void Bullet::draw() {
  display.drawPixel(x, y, SH110X_WHITE);
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

  if (x <= 0 || x >= 128) {
    onLimit = true;
  }

  if (y <= 0 || y >= 64) {
    onLimit = true;
  }
  
}

void Bullet::impact(int tankX, int tankY) {
  // holder pum
}