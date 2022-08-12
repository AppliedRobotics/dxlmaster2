#include <DxlMaster_v2.h>


//#include "DxlMaster.h"

const long unsigned int baudrate = 57600;

// Use broadcast address to affect all connected motors
DynamixelDevice broadcast_device(BROADCAST_ID);
DynamixelDevice device_04(0x04);

uint8_t led_state = true;

void setup() {
  DxlMaster.begin(baudrate);
  delay(100);
}

void loop() {
  broadcast_device.write_v2(DYN_ADDRESS_LED, led_state);
  led_state = !led_state;
  delay(1000);
}
