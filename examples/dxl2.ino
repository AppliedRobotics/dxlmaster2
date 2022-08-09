#include <DxlMaster_v2.h>

// Use broadcast address to affect all connected motors
DynamixelDevice broadcast_device(BROADCAST_ID);
DynamixelDevice device_(0x01);

uint8_t led_state = true;

void setup() {
  DxlMaster.begin(57600);
  delay(100);
}

void loop() {
  broadcast_device.write_v2(DYN_ADDRESS_LED, led_state);
  led_state = !led_state;
  delay(1000);
}
