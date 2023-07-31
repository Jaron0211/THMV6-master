#include "THMV6_master.h"

//sensor pin
int thvmtx = 16; //tx pin
int thvmrx = 17; //rx pin
int timeout = 1000; //SoftwareSerial timeout

THMV6 thmv6(thvmtx,thvmrx,timeout); //create sensor object
float read_data[2] = {0.0,0.0}; 

void setup(){
    Serial.begin(9600);
    thmv6.init();
}

void loop(){

    thmv6.ReadTH(read_data);
    float temp = read_data[0];
    float hum = read_data[1];
    Serial.println("Temp: " + String(temp) + ", Humity: " + String(hum));

    delay(1000);
}