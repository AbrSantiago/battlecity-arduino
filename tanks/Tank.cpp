#include "Tank.h"
#include <Arduino.h>
#include "Bullet.h"

extern Adafruit_SH1106G display;

Tank::Tank(int player_code, int startX, int startY, const unsigned char* tankBitmap, int startDir, Keypad* tankKeypad)
  : id(player_code), x(startX), y(startY), bitmap(tankBitmap), dir(startDir), keypad(tankKeypad) {}

void Tank::shoot(Bullet* bullet) {
  if(!bullet->inUse){
    analogWrite(11, 255);
    delay(50);
    analogWrite(11, 0);
    if(id==0){
      bullet->x = x+11;
    } else {
      bullet->x = x-1;
    }
    bullet->y = y+4;
    bullet->dir = dir;
    bullet->inUse = true;
  }
}

bool Tank::checkCollision(Bullet* bullet) {
  return x <= bullet->x && x+10 >= bullet->x && y <= bullet->y+2 && y+10 >= bullet->y;
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
  display.drawBitmap(x, y, bitmap, 11, 11, SH110X_WHITE);
}

void Tank::processMovement1(int pressedKey) {
  switch (pressedKey) {
    case 'W': x = min(x + 1, 118); break;
    case 'A': y = max(0, y - 1); break;
    case 'S': x = max(0, x - 1); break;
    case 'D': y = min(56, y + 1); break;
    default: break;
  }
}

void Tank::processMovement2(int pressedKey) {
   switch (pressedKey) {
    case 'W': x = max(0, x - 1); break;
    case 'A': y = min(52, y + 1); break;
    case 'S': x = min(116, x + 1); break;
    case 'D': y = max(0, y - 1); break;
    default: break;
  }
}
