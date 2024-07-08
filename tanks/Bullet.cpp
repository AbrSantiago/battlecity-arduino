#include "Bullet.h"
#include <Arduino.h>

extern Adafruit_SH1106G display;

Bullet::Bullet(int x, int y, int dir, const unsigned char* bulletBitmap)
  : x(x), y(y), dir(dir), bitmap(bulletBitmap) {}

void Bullet::move() {
  switch (dir) {
    case 1: x++; break; // Derecha
    case 3: x--; break; // Izquierda
    default: break;
  }
  if (x < 0 || x > 128 || y < 0 || y > 64) {
    inUse = false;
  }
}

void Bullet::draw() {
  display.drawBitmap(x, y, bitmap, 3, 3, SH110X_WHITE);
}