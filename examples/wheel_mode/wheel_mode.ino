// Test motor wheel mode
#include "DxlMaster_v2.h"

// id of the motor
const uint8_t id = 1;
// speed, between -1023 and 1023
int16_t speed = 100;
// communication baudrate
const long unsigned int baudrate = 57600;

DynamixelMotor motor(id);

void setup() 
{
    DxlMaster.begin(baudrate);
    Serial.begin(9600);
    delay(100);

    // check if we can communicate with the motor
    // if not, we stop here
    uint8_t status = motor.init();
    if (status != DYN_STATUS_OK) {
        while (1) {
            Serial.println(status);
            delay(3000);
        }
    }

    motor.enableTorque();
    motor.wheelMode();
}

//change motion direction every 5 seconds
void loop() {
  motor.speed(speed);
  speed = -speed;
  delay(3000);
}