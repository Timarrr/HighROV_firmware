
/*
 Name:		rov_firmware.ino
 Created:	15.01.2018 14:16:59
 Author:	zinjk
*/

#include <Arduino.h>
#include <Wire.h>
#include "HighROV.h"
#include <time.h>

bool wait_for_serial = 1; // change to 1 to enable waiting for serial connection for <wait_for_serial_time> millisecondssecs
int wait_for_serial_time = 5000; //milliseconds


void setup() {
    Wire.begin();
    Wire.setTimeout(1000);
    Wire.setClock(10000);

    delay(100);

    SerialUSB.begin(115200);
    unsigned int t_on = millis();
    while(!SerialUSB && wait_for_serial){
      if(millis() >= t_on + wait_for_serial_time){  
        break;
      }else{
        analogWrite(LED_BUILTIN, sin(millis() * 0.05) * 127 + 127);
        delay(1);
      }
    }
    if(wait_for_serial){
      delay(200);
    }
    // Serial.begin(115200);
    // Serial1.begin(115200);

    HighROV::init();
}



void loop() {
    HighROV::run();
}
