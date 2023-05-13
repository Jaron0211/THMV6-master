#include "modbusmaster.h"

//sensor pin
int tx = 16;
int rx = 17;
int timeout = 1000;

THMV6 thmv6(tx,rx,timeout);

void setup(){
    Serial.begin(9600);
    thmv6.init();
}

void loop(){
    float read_data[2] = {0.0,0.0}; 
    thmv6.ReadTH(read_data);
    float temp = read_data[0];
    float hum = read_data[1];
    Serial.println("Temp: " + String(temp) + ", Humity: " + String(hum));

    delay(1000);
}
