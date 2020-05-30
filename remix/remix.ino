
 #include "Si7021.h"

Si7021 si7021;

void setup()
{
  uint64_t serialNumber = 0ULL;
  Serial.begin(9600);     
  si7021.begin();

  serialNumber = si7021.getSerialNumber();
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

  Serial.print(sensorValue);
  Serial.print(',');
  Serial.print(si7021.getTemperatureFromPreviousHumidityMeasurement());
  Serial.print(',');
  Serial.print(si7021.measureHumidity());
  Serial.print(',');
  Serial.print(wind_speed_m_s);
  Serial.println(' ');


  delay(1000);                           //输出完成后等待0.1秒钟，用于控制数据的刷新速度。

}
