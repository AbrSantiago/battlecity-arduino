#include "Tank.h"
#include <Arduino.h>
#include "Bullet.h"

extern Adafruit_SH1106G display;

Tank::Tank(int player_code, int startX, int startY, const unsigned char* tankBitmap, int startDir, Keypad* tankKeypad)
  : id(player_code), x(startX), y(startY), bitmap(tankBitmap), dir(startDir), keypad(tankKeypad), numBullets(0) {}

Bullet Tank::shoot() {
  // borrar
  Bullet b(x, y, dir); 
  return b;
}

void Tank::move() {
  keypad->getKeys();
  for (int i = 0; i < LIST_MAX; i++) {
    if (keypad->key[i].stateChanged) {
      if (keypad->key[i].kstate == PRESSED || keypad->key[i].kstate == HOLD) {
        if(id == 0) {
          processMovement1(keypad->key[i].kchar);
        } else {
          processMovement2(keypad->key[i].kchar);
        }
      }
    }
  }
}

void Tank::draw() {
  display.drawBitmap(x, y, bitmap, 10, 7, SH110X_WHITE);
}

void Tank::processMovement1(int pressedKey) {
  switch (pressedKey) {
    case 'W':
      dir = 1;
      x = min(x + 1, 118);
      break;
    case 'A':
      dir = 0;
      y = max(0, y - 1);
      break;
    case 'S':
      dir = 3;
      x = max(0, x - 1);
      break;
    case 'D':
      dir = 2;
      y = min(56, y + 1);
      break;
    default:
      break;
  }
}

void Tank::processMovement2(int pressedKey) {
   switch (pressedKey) {
    case 'W':
      dir = 3;
      x = max(0, x - 1);
      break;
    case 'A':
      dir = 2;
      y = min(52, y + 1);
      break;
    case 'S':
      dir = 1;
      x = min(116, x + 1);
      break;
    case 'D':
      dir = 0;
      y = max(0, y - 1);
      break;
    default:
      break;
  }
}
