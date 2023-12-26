#include <DxlMaster2.h>

const unsigned long dynamixel_baudrate = 57600;
const unsigned long serial_baudrate = 57600;

// This example uses Dynamixel 1.0 protocol 
DynamixelConsole console(Serial, 1);

void setup() {
  // Serial port of Dynamixel interface is standard in this example (This default 
  // port depends on your board). Tx/Rx direction pins are default in this example
  // (These default pins depend on your board)
  DxlMaster.begin(dynamixel_baudrate);
  Serial.begin(serial_baudrate);
}

void loop() {
  console.loop();
}
