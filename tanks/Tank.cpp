#include "Tank.h"
#include <Arduino.h>

extern Adafruit_SH1106G display;

Tank::Tank(int startX, int startY, const unsigned char* tankBitmap, int startDir, Keypad* tankKeypad)
  : x(startX), y(startY), bitmap(tankBitmap), dir(startDir), keypad(tankKeypad) {}

void Tank::move() {
  keypad->getKeys();
  for (int i = 0; i < LIST_MAX; i++) {
    if (keypad->key[i].stateChanged) {
      if (keypad->key[i].kstate == PRESSED || keypad->key[i].kstate == HOLD) {
        processMovement(keypad->key[i].kchar);
      }
    }
  }
}

void Tank::draw() {
  display.drawBitmap(x, y, bitmap, 10, 7, SH110X_WHITE);
}

void Tank::processMovemen1(int pressedKey) {
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

void Tank::processMovemen2(int pressedKey) {
  switch (pressedKey) {
    case 'W':
      dir = 3;
      x = min(x + 1, 118);
      break;
    case 'A':
      dir = 2;
      y = max(0, y - 1);
      break;
    case 'S':
      dir = 1;
      x = max(0, x - 1);
      break;
    case 'D':
      dir = 0;
      y = min(56, y + 1);
      break;
    default:
      break;
  }
}

void Tank::shoot() {

}