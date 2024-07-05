#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Keypad.h>
#include "Tank.h"
#include "Bullet.h"

#define i2c_Address 0x3c // Inicializa con la dirección I2C 0x3C
#define SCREEN_WIDTH 128 // Ancho de la pantalla OLED en píxeles
#define SCREEN_HEIGHT 64 // Altura de la pantalla OLED en píxeles
#define OLED_RESET -1    // Reset de QT-PY / XIAO

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Bitmap del tanque de guerra (11x11 píxeles)
static const unsigned char PROGMEM tankBitmap[] = {
  B11111111, B10000000,
  B11111111, B10000000,
  B11111111, B10000000,
  B00111110, B00000000,
  B01100110, B00100000,
  B01100111, B11100000,
  B01100110, B00100000,
  B11111110, B00000000,
  B11111111, B10000000,
  B11111111, B10000000,
  B11111111, B10000000,
};

const byte ROWS = 2; // four rows
const byte COLS = 3; // four columns
char hexaKeys[ROWS][COLS] = {
  {'Q', 'W', 'E'},
  {'A', 'S', 'D'}
};

byte rowPinsA[ROWS] = {13, 12}; // connect to the row pinouts of the keypad
byte colPinsA[COLS] = {10, 9, 8}; // connect to the column pinouts of the keypad
byte rowPinsB[ROWS] = {7, 6}; // connect to the row pinouts of the keypad
byte colPinsB[COLS] = {4, 3, 2}; // connect to the column pinouts of the keypad

Keypad playerAKeypad = Keypad(makeKeymap(hexaKeys), rowPinsA, colPinsA, ROWS, COLS);
Keypad playerBKeypad = Keypad(makeKeymap(hexaKeys), rowPinsB, colPinsB, ROWS, COLS);

Tank playerA(0, 10, 22, tankBitmap, 1, &playerAKeypad);
Tank playerB(1, 108, 38, tankBitmap, 3, &playerBKeypad);

Bullet* bulletA = nullptr;
Bullet* bulletB = nullptr;

void setup() {
  Serial.begin(9600);
  // Inicializa la pantalla OLED
  delay(250); // Espera a que la OLED se encienda
  display.begin(i2c_Address, true); // Dirección 0x3C por defecto
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  playerA.move();
  playerB.move();

  playerA.shoot(bulletA);
  playerB.shoot(bulletB);

  display.clearDisplay();
  playerA.draw();
  playerB.draw();

  if (bulletA != nullptr) {
    if(bulletA->onLimit) {
      bulletA = nullptr;
    }
    bulletA->draw();
  }

  if (bulletB != nullptr) {
    if(bulletB->onLimit) {
      bulletB = nullptr;
    }
    bulletB->draw();
  }

  display.display();
  delay(5);
}