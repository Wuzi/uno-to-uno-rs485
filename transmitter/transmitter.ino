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

// Codes
#define TURN_LED_ON   'a'
#define TURN_LED_OFF  'b'

// Create the SoftwareSerial to make the connection with the RS485 module
SoftwareSerial RS485Serial(RS485_RX_PIN, RS485_TX_PIN);

void setup()
{
  Serial.begin(9600);
  Serial.println("== TRANSMITTER ==");

  // Set the transmission pin to output
  pinMode(SERIAL_TX_CONTROL_PIN, OUTPUT);

  // Start the RS485 module serial
  RS485Serial.begin(4800);
  pinMode(A0, INPUT_PULLUP);

  delay(100);

  // Set the transmission pin to as transmitter
  digitalWrite(SERIAL_TX_CONTROL_PIN, RS485_TRANSMIT);
}

// Send codes to the receiver every 10 seconds
bool blink = false;
void loop()
{
  blink = !blink;
  RS485Serial.print(blink ? TURN_LED_ON : TURN_LED_OFF);
  delay(10000);
}
