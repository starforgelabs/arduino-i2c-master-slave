#include <Wire.h>

//
// i2c_test_01
//
// This demonstrates a master transmitting to a slave.
// 
// The master transmits a value read from an analogue port.
// The slave sends the value to the serial device.
//

const byte SlaveDeviceId = 1;

void setup()
{
  // Start I²C bus as a slave
  Wire.begin(SlaveDeviceId); 
  // Set the callback to call when data is received. 
  Wire.onReceive(receiveCallback);
  
  // For demonstration purposes.
  Serial.begin(9600);
}

void loop()
{
}

// aCount is the number of bytes received.
void receiveCallback(int aCount)
{
  if(aCount == 2)
  {
    int receivedValue  = Wire.read() << 8; 
    receivedValue |= Wire.read();
    Serial.println(receivedValue);
  }
  else
  {
    Serial.print("Unexpected number of bytes received: ");
    Serial.println(aCount);
  }
}

