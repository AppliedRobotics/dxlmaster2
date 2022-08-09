// Test motor wheel mode
#define VERSION 2

#if (VERSION == 1)
    #include "DxlMaster.h"
#else
    #include "DxlMaster_v2.h"
#endif

// Use broadcast address to affect all connected motors
DynamixelDevice broadcast_device(BROADCAST_ID);
DynamixelDevice device(0x01);

uint8_t led_state = true;

void setup() {
    DxlMaster.begin(57600);
    Serial.begin(57600);
    Serial.print("Init: ");
    Serial.println(device.init());
    Serial.println(device.write(13,2));
    delay(100);
}

void loop() {
    DynamixelStatus status; 
    //status = device.write_v2(65, led_state);
    status = DxlMaster.write_v2(1, (uint16_t)65, 1, &led_state, 2);
    //uint8_t xxx[250];
    //status = DxlMaster.read_v2(1, 0, 250, xxx);
    Serial.println(status);

    led_state = !led_state;
    delay(1000);
}


DynamixelDevice device(0x01);

void setup() {
    DxlMaster.begin(57600);
    Serial.begin(57600);
    device.init();
    device.write(13,2); // смена протокола
    delay(100);
}

void loop() {
    const uint8_t address = 24;
    const uint8_t size = 10;
    uint8_t buffer[size];
    device.read_v2(address, buffer);
}