#include <Wire.h>

//
// i2c_test_01
//
// This demonstrates a master transmitting to a slave.
// 
// The master transmits a value read from an analogue port.
// The slave sends the value to the serial device.
//

const byte AnalogueInputPin = 0;
const byte SlaveDeviceId = 1;

void setup()
{
  // Start I²C bus as master
  Wire.begin(); 
  
  // For demonstration purposes.
  pinMode(AnalogueInputPin, INPUT);
}

void loop()
{
  int input = analogRead(AnalogueInputPin);
  
  // Send two bytes to slave.
  Wire.beginTransmission(SlaveDeviceId);
  Wire.write(input >> 8);
  Wire.write(input & 255);
  Wire.endTransmission();
  
  delay(1000);
}

