#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Keypad.h>
#include "Tank.h"

#define i2c_Address 0x3c // Inicializa con la dirección I2C 0x3C
#define SCREEN_WIDTH 128 // Ancho de la pantalla OLED en píxeles
#define SCREEN_HEIGHT 64 // Altura de la pantalla OLED en píxeles
#define OLED_RESET -1    // Reset de QT-PY / XIAO

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Bitmap del tanque de guerra (10x7 píxeles)
static const unsigned char PROGMEM tankOneBitmap[] = {
  B11111111, B00000000, // ########00
  B11111111, B00000000, // ########00
  B01111100, B00000000, // 0######000
  B01111111, B11111111, // 0########
  B01111100, B00000000, // 0######000
  B11111111, B00000000, // ########00
  B11111111, B00000000  // ########00
};

static const unsigned char PROGMEM tankTwoBitmap[] = {
  B00111111, B11000000, // 00########
  B00111111, B11000000, // 00########
  B00001111, B10000000, // 000######0
  B11111111, B10000000, // ########0
  B00001111, B10000000, // 000######0
  B00111111, B11000000, // 00########
  B00111111, B11000000  // 00########
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

Tank playerA(10, 22, tankOneBitmap, &playerAKeypad);
Tank playerB(108, 38, tankTwoBitmap, &playerBKeypad);

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

  display.clearDisplay();
  playerA.draw();
  playerB.draw();
  display.display();
  delay(5);
}