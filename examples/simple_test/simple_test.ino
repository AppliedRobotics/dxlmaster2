// Test motor wheel mode
#define VERSION 2

#if (VERSION == 1)
    #include "DxlMaster.h"
#else
    #include "DxlMaster_v2.h"
#endif

#define ADR_LED  65

#define ID_1  0x01
DynamixelDevice device(ID_1);

uint8_t led_state = true;

void setup() {
    DxlMaster.begin(57600);
    Serial.begin(57600);
    Serial.println("Start Simple test scketch");

    device.protocolVersion(2);

    Serial.print("Version: ");
    Serial.println(device.protocolVersion());

    Serial.print("Ping: ");
    Serial.println(device.ping(), HEX);

    delay(500);
}

void loop() 
{
    DynamixelStatus status = 0; 

    Serial.println("\n ***Loop start***");
    
    Serial.print("1. Ping: ");
    status = device.ping();
    if (status == DYN_STATUS_OK)
        Serial.print("\tOk!");
    else
        Serial.print("\tErr!");
    Serial.println(" Status = " + String(status));


    Serial.print("2. Read: ");
    uint8_t id = 0;
    status = device.read(7, id);
    if (id == ID_1) {
        Serial.print("\tOk! ID = ");
        Serial.print(id);
    }
    else {
        Serial.print("\tErr! ID = ");
        Serial.print(id);
    }
    Serial.print(" Status = ");
    Serial.println(status);
    

    Serial.print("3. Write: ");
    //status = device.write(ADR_LED, led_state);
    if (status == DYN_STATUS_OK) {
        Serial.print("\tOk! LED = ");
        Serial.print(led_state);
    }
    else {
        Serial.print("\tErr!");
    }
    led_state = !led_state;
    Serial.print(" Status = ");
    Serial.println(status);


    Serial.print("4. Reg Write ");
    //status = device.regWrite(ADR_LED, led_state);
    if (status == DYN_STATUS_OK) {
        Serial.print("\tOk!");
    }
    else {
        Serial.print("\tErr!");
    }
    led_state = !led_state;
    Serial.print(" Status = ");
    Serial.println(status);


    Serial.print("5. Action ");
    status = device.action();
    Serial.println("\t Always Ok!");


    Serial.print("6. Reset: ");
    status = device.reset(0x02);
    if (status == DYN_STATUS_OK) {
        Serial.print("\tOk!");
    }
    else {
        Serial.print("\tErr!");
    }
    Serial.print(" Status = ");
    Serial.println(status);

    
    Serial.print("7. Reboot: ");
    status = device.reboot();
    if (status == DYN_STATUS_OK) {
        Serial.print("\tOk!");
    }
    else {
        Serial.print("\tErr!");
    }
    Serial.print(" Status = ");
    Serial.println(status);

    Serial.print("x. Sync Write: ");
    uint8_t arr_id[1] = {1};
    status = device.syncWrite(1, arr_id, ADR_LED, 1, &led_state);
    if (status == DYN_STATUS_OK) {
        Serial.print("\tOk! LED = ");
        Serial.print(led_state);
    }
    else {
        Serial.print("\tErr!");
    }
    led_state = !led_state;
    Serial.print(" Status = ");
    Serial.println(status);

    


    //Serial.println(device.write(65, 1, &led_state));
    //status = DxlMaster.write_v2(1, (uint16_t)65, 1, &led_state, 2);

    //uint8_t xxx[25];
    //status = device.read(1, 25, xxx);
    //Serial.println(status);

    
    delay(5000);
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