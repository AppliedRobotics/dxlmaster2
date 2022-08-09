// Test motor wheel mode
#define VERSION 2

#if VERSION == 1
    #include "DxlMaster.h"
#else
    #include "DxlMaster_v2.h"
#endif



// id of the motor
const uint8_t id = 1;
// speed, between -1023 and 1023
int16_t speed = 200;
// communication baudrate
const long unsigned int baudrate = 57600;

DynamixelMotor motor(id);

void setup() 
{
    DxlMaster.begin(baudrate);
    Serial.begin(57600);
    Serial.println("Hello!");
    delay(100);


    // check if we can communicate with the motor
    // if not, we stop here
    uint8_t status = motor.init();
    if (status != DYN_STATUS_OK) {
        while (1) {
            Serial.println(motor.init());
            delay(100);
        }
    }

    motor.enableTorque(); 
    motor.wheelMode(); 

    //write(DYN_ADDRESS_ENABLE_TORQUE, uint8_t(aTorque?1:0));
   
    //uint32_t data= (aCWLimit | (uint32_t(aCCWLimit)<<16));
	//write(DYN_ADDRESS_CW_LIMIT, data);
}

//change motion direction every 5 seconds
void loop() {
    Serial.println("Loop..");
    motor.speed(speed);
    speed = -speed;
    delay(3000);
}