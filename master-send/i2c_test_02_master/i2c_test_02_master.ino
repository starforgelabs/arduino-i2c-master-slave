#include <Wire.h>

//
// i2c_test_02
//
// This demonstrates a slave transmitting to a master.
// 
// The master requests a value from the slave and sends
// it to the serial device. 
// The slave reads from an analogue port and transmits it
// to the master. 
//

const byte SlaveDeviceId = 1;

void setup()
{
  // Start I²C bus as master
  Wire.begin(); 
  
  // For demonstration purposes.
  Serial.begin(9600);
}

void loop()
{
  
  // Request data from slave.
  Wire.beginTransmission(SlaveDeviceId);
  int available = Wire.requestFrom(SlaveDeviceId, (uint8_t)2);
  
  if(available == 2)
  {
    int receivedValue = Wire.read() << 8 | Wire.read(); 
    Serial.println(receivedValue);
  }
  else
  {
    Serial.print("Unexpected number of bytes received: ");
    Serial.println(available);
  }

  int result = Wire.endTransmission();
  if(result)
  {
    Serial.print("Unexpected endTransmission result: ");
    Serial.println(result);
  }
  
  delay(1000);
}

