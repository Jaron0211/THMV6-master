/*
  Author: Jian Lun, Lee
  Date: 2023/05/12
  Version: 0.0.1-preview
  Platform: ESP32-AIOT AirBox

  CAUTION:
  THIS CODE IS ONLY FOR TEST PURPOSE, DON'T USE IN COMMERCIAL.
*/

#ifndef THMV6_h
#define THMV6_h

#include <SoftwareSerial.h>
#include <Arduino.h>

extern int thvmtx,thvmrx;

class THMV6 {  

  public:
    
    THMV6(int _com_port_tx, int _com_port_rx, int _timeout): com_port_tx(_com_port_tx), com_port_rx(_com_port_rx), timeout(_timeout)
    {
    };

    int com_port_tx ;
    int com_port_rx ;

    void CRC16(char *pushMsg, unsigned short usDataLen);

    void init();
    float ReadTH(float output[2]);

    unsigned long send_cooldown_timer = millis();
    int timeout = 1000;

    int send_command[8] = {0x01, 0x03, 0x00, 0x02, 0x00, 0x02, 0x65, 0xCB};

    
};
#endif