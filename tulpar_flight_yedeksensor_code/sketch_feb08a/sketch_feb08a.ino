#include <MPU6050.h>
#include <Wire.h>

MPU6050 sensor;

int ivmeX , ivmeY , ivmeZ , GyroX , GyroY , GyroZ;
int i=0;
int j=0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  sensor.initialize();
}

void loop() {
  sensor.getMotion6(&ivmeX, &ivmeY, &ivmeZ, &GyroX, &GyroY, &GyroZ);

  i = analogRead(A5);
  j = analogRead(A4);

     if(Serial.read()=='1')
  {
    Serial.print(i);
    Serial.print("*");
    Serial.print(j); 
    Serial.print("*");
    Serial.print(ivmeX);//ivme X
    Serial.print("*");
    Serial.print(ivmeY);//ivme y
    Serial.print("*");
    Serial.print(ivmeZ);//ivme z
    Serial.print("*");
    Serial.print(GyroX);//gyro x
    Serial.print("*");
    Serial.print(GyroY);//gyro y
    Serial.print("*");
    Serial.println(GyroZ);//gyro z

  } 
   delay(5);

}
