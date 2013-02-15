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

const byte AnalogueInputPin = 0;
const byte SlaveDeviceId = 1;

void setup()
{
  // Start I²C bus as a slave
  Wire.begin(SlaveDeviceId); 
  // Set the callback to call when data is requested. 
  Wire.onRequest(requestCallback);
}

void loop()
{
}

void requestCallback()
{
  int input = analogRead(AnalogueInputPin);
  
  // Send two bytes to master.
  //
  // IMPORTANT NOTE FOR ARDUINO 1.0.3
  // (I've not looked at other Arduino Wire versions.) 
  //
  // The behaviour of Wire.write() is asymmetric; its behaviour
  // depends on whether you're a master or slave. 
  //
  // Calling write() from the master fills a 32-byte buffer 
  // which is transmitted when endTransmission() is called. 
  //
  // Calling write() from the slave sends the data immediately.
  // If you call write(uint8_t), you send one byte (extra
  // bytes requested by the server are garbage).
  //
  // If you look in the library code included with the 
  // Arduino (1.0.3), to send multiple bytes from the slave, 
  // you have to fill your own buffer and send it all at once.
  //
  uint8_t buffer[2];
  buffer[0] = input >> 8;
  buffer[1] = input & 0xff;  
  Wire.write(buffer, 2);
}

