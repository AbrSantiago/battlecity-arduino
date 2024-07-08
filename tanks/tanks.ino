#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Keypad.h>
#include "Tank.h"
#include "Bullet.h"

#define i2c_Address 0x3c // Inicializa con la dirección I2C 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Bitmap del tanque de guerra (11x11 píxeles)
static const unsigned char PROGMEM tankBitmapA[] = {
  B11111111, B10000000,
  B11111111, B10000000,
  B11111111, B10000000,
  B01111110, B00000000,
  B01100110, B00100000,
  B01100111, B11100000,
  B01100110, B00100000,
  B01111110, B00000000,
  B11111111, B10000000,
  B11111111, B10000000,
  B11111111, B10000000,
};

static const unsigned char PROGMEM tankBitmapB[] = {
  B00111111, B11100000,
  B00111111, B11100000,
  B00111111, B11100000,
  B00001111, B11000000,
  B10001100, B11000000,
  B11111100, B11000000,
  B10001100, B11000000,
  B00001111, B11000000,
  B00111111, B11100000,
  B00111111, B11100000,
  B00111111, B11100000,
};


static const unsigned char PROGMEM bulletBitmap[] = {
  B11100000,
  B11100000,
  B11100000,
};

const byte ROWS = 2;
const byte COLS = 3;
char hexaKeys[ROWS][COLS] = {
  {'Q', 'W', 'E'},
  {'A', 'S', 'D'}
};

byte rowPinsA[ROWS] = {13, 12};
byte colPinsA[COLS] = {10, 9, 8};
byte rowPinsB[ROWS] = {7, 6};
byte colPinsB[COLS] = {4, 3, 2};

Keypad playerAKeypad = Keypad(makeKeymap(hexaKeys), rowPinsA, colPinsA, ROWS, COLS);
Keypad playerBKeypad = Keypad(makeKeymap(hexaKeys), rowPinsB, colPinsB, ROWS, COLS);

Bullet bullet1 = Bullet(-3, -3, -1, bulletBitmap);

Tank playerA(0, 20, 20, tankBitmapA, 1, &playerAKeypad);
Tank playerB(1, 108, 40, tankBitmapB, 3, &playerBKeypad);

bool impact = false;

void start() {
  // display.write("Battle city");
  display.print("Battle city");
  display.display();
}

void setup() {
  Serial.begin(9600);
  delay(200);
  display.begin(i2c_Address, true);
  display.clearDisplay();
  // start();
  // delay(1000);
}

void loop() {
  if(!impact) {
    playerA.move();
    playerB.move();

    playerAKeypad.getKeys();
    for (int i = 0; i < LIST_MAX; i++) {
      if (playerAKeypad.key[i].stateChanged) {
        if (playerAKeypad.key[i].kstate == PRESSED || playerAKeypad.key[i].kstate == HOLD) {
          switch (playerAKeypad.key[i].kchar) {
            case 'E': playerA.shoot(&bullet1); break;
            case 'Q': playerA.shoot(&bullet1); break;
            default: break;
          }
        }
      }
    }
    
    playerBKeypad.getKeys();
    for (int i = 0; i < LIST_MAX; i++) {
      if (playerBKeypad.key[i].stateChanged) {
        if (playerBKeypad.key[i].kstate == PRESSED || playerBKeypad.key[i].kstate == HOLD) {
          switch (playerBKeypad.key[i].kchar) {
            case 'E': playerB.shoot(&bullet1); break;
            case 'Q': playerB.shoot(&bullet1); break;
            default: break;
          }
        }
      }
    }

    bullet1.move();

    display.clearDisplay();
    playerA.draw();
    playerB.draw();
    bullet1.draw();
    display.display();

    impact = playerA.checkCollision(&bullet1) || playerB.checkCollision(&bullet1);
  } else {
    // muestro pantalla de "Game Over"
    // display.clearDisplay();
    // display.setTextSize(5);
    // display.write("Winner...");
  }

  delay(5);
}