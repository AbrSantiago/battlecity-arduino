#include "Bullet.h"
#include <Arduino.h>
#include "Tank.h"

extern Adafruit_SH1106G display;

Bullet::Bullet(int x, int y, int dir)
  : x(x), y(y), dir(dir) {}

void Bullet::move() {
  switch (dir) {
    case 0: y--; break; // Arriba
    case 1: x++; break; // Derecha
    case 2: y++; break; // Abajo
    case 3: x--; break; // Izquierda
    default: break;
  }
}

  // if (x < 0 || x > 128 || y < 0 || y > 64) {
  //   outOfLimit = true;
  // }
  
// }

// bool Bullet::checkCollision(Tank& tank) {
//   return (x >= tank.x && x <= tank.x + 10) || (y >= tank.y && y <= tank.y + 10);
// }