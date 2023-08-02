#include "THMV6_master.h"

//sensor pin, base on SoftwareSerial
int thvm_tx = 16; //tx pin
int thvm_rx = 17; //rx pin
int timeout = 1000; //SoftwareSerial timeout

THMV6 thmv6(thvm_tx,thvm_rx,timeout); //create sensor object
float read_data[2] = {0.0,0.0}; 

void setup(){
    Serial.begin(9600);
    thmv6.init(9600);
}

void loop(){

    thmv6.ReadTH(read_data);
    float temp = read_data[0];
    float hum = read_data[1];
    Serial.println("Temp: " + String(temp) + ", Humity: " + String(hum));

    delay(1000);
}