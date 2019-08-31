/**
 * Communication between Arduino to Arduino using RS485 - Transmitter
 */
#include <SoftwareSerial.h>

// Serial communication pins (RS485 Module)
#define RS485_RX_PIN    10
#define RS485_TX_PIN    11

// Transmission PIN
#define SERIAL_TX_CONTROL_PIN 3

// HIGH = Transmit data
// LOW = Receive data
#define RS485_TRANSMIT    HIGH
#define RS485_RECEIVE     LOW

// Create the SoftwareSerial to make the connection with the RS485 module
SoftwareSerial RS485Serial(RS485_RX_PIN, RS485_TX_PIN);

// Bomb pins
#define MAX_BOMB_PINS 4
const int BOMB_PINS[MAX_BOMB_PINS] = {4, 5, 6, 7};

// Bomb codes
// Examples:
// BOMB_CODES[0][0] will return the code for: bomb 1 is ON
// BOMB_CODES[0][1] will return the code for: bomb 1 is OFF
const char BOMB_CODES[MAX_BOMB_PINS][2] = {
// ON   OFF
  {'a', 'b'},
  {'c', 'd'},
  {'e', 'f'},
  {'g', 'h'}
};

void setup()
{
  Serial.begin(9600);
  Serial.println("== TRANSMITTER ==");

  // Set the transmission pin to output
  pinMode(SERIAL_TX_CONTROL_PIN, OUTPUT);

  // Set bomb pins
  for (int i = 0; i < MAX_BOMB_PINS; i++) {
    pinMode(BOMB_PINS[i], INPUT_PULLUP);
  }

  // Start the RS485 module serial
  RS485Serial.begin(4800);
  delay(100);

  // Set the transmission pin to as transmitter
  digitalWrite(SERIAL_TX_CONTROL_PIN, RS485_TRANSMIT);
}

// Send codes to the receiver every 10 seconds
void loop()
{
  // Send bomb info to receiver
  for (int i = 0; i < MAX_BOMB_PINS; i++) {
    int state = digitalRead(BOMB_PINS[i]);
    RS485Serial.print(BOMB_CODES[i][state]);
  }
  delay(10000);
}
