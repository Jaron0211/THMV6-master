#include <HardwareSerial.h>
HardwareSerial tempHumidSensor(2);//創建一個新的Serial物件,命名為tempHumidsensor

void setup() {
    tempHumidSensor.begin(9600,SERIAL_6N1,16,17//初始化电口,使用9600波特率,個數位,校驗位,個停业位,使用GPI016料
    Serial.begin(9600);// 初始化另一個串口,用於顯示接收到的數據
}

void loop(){
    //讀取溫濕度資料的指令:01 03 00 02 00 02 65 CB
    byte readTempHumidCmd[] = {0x01, 0x03, 0x00, 0x02, 0x00, 0x02, 0x65, 0xCB};

    //先發送指令給感測器
    tempHumidSensor.flush();
    tempHumidSensor.write(readTempHumidCmd,sizeof(readTempHumidCmd));
    delay(50);//等待感測器回應

    if(tempHumidSensor.available()){// 檢查是否有可用的數
        byte tempHumidData[9];//創建一個數維來存儲接收到的數
        tempHumidSensor.readBytes(tempHumidData,9);//讀取9個字飾的數,存储到tempHumidData数維中
        //解析回應,獲取溫濕度資料
        byte tempHigh = tempHumidData[3];
        byte tempLow = tempHumidData[4] ;
        byte humidHigh = tempHumidData[5];
        byte humidLow = tempHumidData[6];

        int temperatureRaw = (tempHigh << 8) | tempLow;
        int humidityRaw = (humidHigh << 8) | humidLow;
        //根據資料解析方式轉換溫度和濕度數值
        float temperature = temperatureRaw / 10.0;
        float humidity = humidityRaw / 10.0;
        //顯示溫濕度資訊
        Serial.print("Temperature: ");
        Serial.print(temperature) ;
        Serial.print(" *C, Humidity: ");
        Serial.print(humidity) ;
        Serial.println(" %RH") ;
    }
    delay(500);//每隔0.5秒讀取一次
}