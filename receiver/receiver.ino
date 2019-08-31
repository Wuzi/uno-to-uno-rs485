/**
 * Communication between Arduino to Arduino using RS485 - Receiver
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
  Serial.println("== RECEIVER ==");

  // Led pin
  pinMode(A0, OUTPUT);
  
  // Set the transmission pin to output
  pinMode(SERIAL_TX_CONTROL_PIN, OUTPUT);

  // Start the RS485 module serial
  RS485Serial.begin(4800);

  // Set the transmission pin to as receiver
  digitalWrite(SERIAL_TX_CONTROL_PIN, RS485_RECEIVE);
}

void loop()
{
  // Receive data through serial port
  if (RS485Serial.available())
  {
    while (RS485Serial.available())
    {
      // Read data
      char code = RS485Serial.read();
      switch (code) {
        case TURN_LED_ON:
          digitalWrite(A0, HIGH);
          break;
        case TURN_LED_OFF:
          digitalWrite(A0, LOW);
          break;
      }
    }
  }
}
