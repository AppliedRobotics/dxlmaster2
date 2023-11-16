#include "DxlMaster2.h"

// This example shows a simple request-response communication with
// Applied Robotics Dynamixel push button
// You can specify your custom hardware serial port and Tx/Rx direction pins for Dynamixel
// interface with DxlMaster.begin() method

#define AR_DXL_BUTTON_ID 0x03
#define AR_DXL_BUTTON_STATE_ADR 27

DynamixelDevice device(AR_DXL_BUTTON_ID);

uint8_t button_state = 0;

void setup() {
    // Pass a pointer to HardwareSerial object to specify serial
    DxlMaster.begin(57600, &Serial1, 21, 20);
    Serial.begin(57600);

    device.protocolVersion(1);

    Serial.print("Version: ");
    Serial.println(device.protocolVersion());
    
    Serial.print("\r\nPing/read test start. Device model: ");
    Serial.println(device.model());
}

void loop() {
    Serial.print("Ping return code: ");
    Serial.println(device.ping(), HEX);
    
    device.read(AR_DXL_BUTTON_STATE_ADR, button_state);
    Serial.print("Button pressed: ");
    Serial.println(button_state);
    
    delay(1000);
}
