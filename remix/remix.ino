//#include <OneWire.h>
//#include <DallasTemperature.h>
 #include "Si7021.h"

Si7021 si7021;

// Data wire is plugged into pin 2 on the Arduino
//#define ONE_WIRE_BUS 2
 
// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
//OneWire oneWire(ONE_WIRE_BUS);
 
// Pass our oneWire reference to Dallas Temperature.
//DallasTemperature sensors(&oneWire);

void setup()
{
  uint64_t serialNumber = 0ULL;
  Serial.begin(9600);     //使用9600的波特率进行串口通讯
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
//  sensors.begin();
  si7021.begin();

  serialNumber = si7021.getSerialNumber();

  //arduino lib doesn't natively support printing 64bit numbers on the serial port
  //so it's done in 2 times
  Serial.print("Si7021 serial number: ");
  Serial.print((uint32_t)(serialNumber >> 32), HEX);
  Serial.println((uint32_t)(serialNumber), HEX);

  //Firware version
  Serial.print("Si7021 firmware version: ");
  Serial.println(si7021.getFirmwareVersion(), HEX);
}

void loop()
{
  float sensorVoltage;
  float sensorValue;
  int V1 = analogRead(A0);  //从A1口读取电压数据存入刚刚创建整数型变量V1，模拟口的电压测量范围为0-5V 返回的值为0-1024
  if (V1 < 2) V1 = 0;  //过滤杂波
  float vol = V1 * (5.0 / 1023.0);//我们将 V1的值换算成实际电压值存入浮点型变量 vol

  float wind_speed_km_h = 100.0 * vol;//电压值转换为风速值km/h
  float wind_speed_m_s = 27.8 * vol;//电压值转换为风速值m/s

  sensorValue = analogRead(A1);
  sensorVoltage = sensorValue/1024*3.3;

  Serial.print("wind speed: ");
  Serial.print(vol);                       //串口输出电压值，并且不换行
  Serial.print(" V    ");
  Serial.print(wind_speed_km_h);
  Serial.print(" km/h   ");
  Serial.print(wind_speed_m_s);
  Serial.print(" m/s");
  Serial.print(" \n");

  Serial.print("uv: ");
  Serial.print("sensor reading = ");
  Serial.print(sensorValue);
  Serial.println("");
  Serial.print("sensor voltage = ");
  Serial.print(sensorVoltage);
  Serial.println(" V");
  Serial.print(" \n");
  
//  // call sensors.requestTemperatures() to issue a global temperature
//  // request to all devices on the bus
//  Serial.print(" Requesting temperatures...");
//  sensors.requestTemperatures(); // Send the command to get temperatures
//  Serial.print(" \n");
//
//  Serial.print("Temperature is: ");
//  Serial.print(sensors.getTempCByIndex(0)); // Why "byIndex"? 
//  // You can have more than one IC on the same bus. 
//  // 0 refers to the first IC on the wire
//  Serial.print(" \n");
  
  Serial.print("water Humidity: ");
  Serial.print(si7021.measureHumidity());
  Serial.print("% - Temperature: ");
  Serial.print(si7021.getTemperatureFromPreviousHumidityMeasurement());
  Serial.println("C");
  Serial.println("DONE");
  delay(5000);                           //输出完成后等待0.1秒钟，用于控制数据的刷新速度。

}
