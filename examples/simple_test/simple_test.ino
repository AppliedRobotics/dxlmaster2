// Test motor wheel mode
#define VERSION 2

#if (VERSION == 1)
    #include "DxlMaster.h"
#else
    #include "DxlMaster_v2.h"
#endif




// Use broadcast address to affect all connected motors

DynamixelDevice device(0x01);

uint8_t led_state = true;

void setup() {
    DxlMaster.begin(57600);
    Serial.begin(57600);
    Serial.println("Start");
    Serial.print("Version: ");
    Serial.println(device.protocolVersion());
    device.protocolVersion(2);
    Serial.print("Ping: ");
    Serial.println(device.ping());

    device.write(11, (uint8_t) 4);
    //device.write(64, 1);
    delay(100);
}

void loop() 
{
    DynamixelStatus status = 0; 
    static uint32_t pos = 0;
    uint16_t address = 116;

    //device.write(65, 1, &led_state);
    
    //Serial.print(device.read(address, pos));
    //Serial.print(" ");
    //Serial.print(++pos);
    Serial.println(pos);
    device.write(address, pos);
    pos += 100;


    //Serial.println(device.write(65, 1, &led_state));
    //status = DxlMaster.write_v2(1, (uint16_t)65, 1, &led_state, 2);

    //uint8_t xxx[25];
    //status = device.read(1, 25, xxx);
    //Serial.println(status);

    led_state = !led_state;
    delay(100);
}

/*
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
}*/