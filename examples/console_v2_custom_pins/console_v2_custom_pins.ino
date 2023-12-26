#include <DxlMaster2.h>

// This is a basic console that allow you to experiment easily with your servos 
// and other Dynamixel devices from the arduino hardware serial terminal
// You can specify your custom hardware serial port and Tx/Rx direction pins for Dynamixel
// interface with DxlMaster.begin() method
//
// For now, only a few low level functions are implemented.
// Call "help" to get a list of the commands.
// You can find the register description table in the doc directory usefull
// Note that all values, including adresses must be passed in decimal format

const unsigned long dynamixel_baudrate = 57600;
const unsigned long serial_baudrate = 57600;

// This example uses Dynamixel 2.0 protocol
DynamixelConsole console(Serial, 2);

void setup() {
  // Pass a pointer to standard serial port Serial1 (HardwareSerial object) of Dynamixel interface 
  // before custom Tx/Rx direction pins (These direction pins relate to TECHNOLAB ATmega2560 board)
  DxlMaster.begin(dynamixel_baudrate, &Serial1, 21, 20);
  Serial.begin(serial_baudrate);
}

void loop() {
  console.loop();
}
