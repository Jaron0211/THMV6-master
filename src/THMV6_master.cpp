/*
  Author: Jian Lun, Lee
  Date: 2023/05/12
  Version: 1.0.0
  Platform: ESP32-AIOT AirBox

  CAUTION:
  THIS CODE IS ONLY FOR TEST PURPOSE, DON'T USE IN COMMERCIAL.
*/

#include "THMV6_master.h"
#include <Arduino.h>

THMV6::~THMV6()
{
  if(THMV6_serial != NULL) free(THMV6::THMV6_serial);
}

void THMV6::CRC16(char *pushMsg, unsigned short usDataLen)
{
  Serial.println("pui pui");
}

void THMV6::init(int baudrate)
{
  THMV6::THMV6_serial = new SoftwareSerial(THMV6::com_port_tx,THMV6::com_port_rx);
  THMV6::THMV6_serial -> begin(baudrate);
}

float THMV6::ReadTH(float output[2]) {

  float return_int[2];

  for ( int i; i < 9; i++) {
    THMV6::THMV6_serial -> write(THMV6::send_command[i]);
  }

  int income_counter = 0;
  int data_buffer[9];
  unsigned long timeout_timer = millis();
  bool success_read = false;

  while (true) {
    if (THMV6::THMV6_serial -> available()) {
      int _buf = THMV6::THMV6_serial -> read();
      //Serial.println(_buf);
      data_buffer[income_counter] = _buf;
      ++income_counter;
      timeout_timer = millis();
    }

    if (millis() - timeout_timer >= THMV6::timeout) {
      return_int[0] = -1;
      return_int[1] = -1;
      success_read = false;
      break;
    }

    if (income_counter == 9) {
      success_read = true;
      break;
    }
  }

  if (success_read) {
    long temp = data_buffer[3] << 8 | data_buffer[4] ;
    long hum  = data_buffer[5] << 8 | data_buffer[6] ;
    return_int[0] = (temp*0.1) ;
    return_int[1] = (hum*0.1);
  }

  output[0] = return_int[0];
  output[1] = return_int[1];
}
