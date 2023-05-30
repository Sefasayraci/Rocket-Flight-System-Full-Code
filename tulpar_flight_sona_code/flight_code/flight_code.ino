#include <Adafruit_BMP085.h>
#include <MPU6050.h>
#include <Wire.h>

MPU6050 sensor;
Adafruit_BMP085 bmp;

int ivmeX, ivmeY, ivmeZ, GyroX, GyroY, GyroZ;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  sensor.initialize();
  
  if (!bmp.begin()) {
  while (1) {}
  }
}
  
void loop() {
  
sensor.getMotion6(&ivmeX, &ivmeY, &ivmeZ, &GyroX, &GyroY, &GyroZ);

//if(Serial.read()=='1'){
   /* Serial.print(bmp.readTemperature());// Sıcaklık *C
    Serial.print("*");
    Serial.print(bmp.readPressure());// Basınç Pa
    Serial.print("*");
    Serial.print(bmp.readAltitude());// Rakım meters
    Serial.print("*");
    Serial.print(bmp.readSealevelPressure());// Deniz Seviyesi Basınç  Pa
    Serial.print("*");
    Serial.print(bmp.readAltitude(101500));// Gerçek Rakım meters
    Serial.print("*");*/
    Serial.print(ivmeZ);//ivme z                                            // HIZ VERİSİ Mİ ?
    Serial.print("/");
    Serial.print(ivmeX);//ivme X
    Serial.print("/");
    Serial.print(ivmeY);//ivme y
    Serial.print("/");
    Serial.print(ivmeZ);//ivme z
    Serial.print("/");
    Serial.print(GyroX);//gyro x
    Serial.print("/");
    Serial.print(GyroY);//gyro y
    Serial.print("/");
    Serial.println(GyroZ);//gyro z
//}
     delay(5);                                                             // GECİKM SĞRESİ INTERFACE ÜZERİNDE YAPILDI INTERVAL DEĞERİ=1000 = 1 SN
}
