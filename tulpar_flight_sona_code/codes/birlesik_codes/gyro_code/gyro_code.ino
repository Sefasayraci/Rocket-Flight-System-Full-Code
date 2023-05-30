#include <Wire.h>
#include <MPU6050.h>


MPU6050 mpu;

#include "kalman.h"
// Fast Kalman Filter Parameters
double Qparameter = 0.1;      // Covariance Process Noise Coefficient
double Rparameter = 10;       // Covariance Measurement Noise Coefficient
double samplingPeriod = 0.01; // Fixed Sampling time of System
double PNStd = 0.04;          // Initial Process Noise Deviation
double MNstd = 0.04;          // Initial Measurement Noise Deviation
double initialValue = 0;     // Known or estimated Initial Value


struct FastKalmanFilter Xnorm_kalman_result_struct;
struct FastKalmanFilter Ynorm_kalman_result_struct;
struct FastKalmanFilter Znorm_kalman_result_struct;

void setup() 
{
  Serial.begin(9600);

  Serial.println("Initialize MPU6050");

  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  FastKalmanFilter_setup(Xnorm_kalman_result_struct,Qparameter, Rparameter, samplingPeriod, PNStd, MNstd, initialValue);
  FastKalmanFilter_setup(Ynorm_kalman_result_struct,Qparameter, Rparameter, samplingPeriod, PNStd, MNstd, initialValue);
  FastKalmanFilter_setup(Znorm_kalman_result_struct,Qparameter, Rparameter, samplingPeriod, PNStd, MNstd, initialValue);

/*
  If you want, you can set accelerometer offsets
  mpu.setAccelOffsetX();
  mpu.setAccelOffsetY();
  mpu.setAccelOffsetZ();
  */
  
  checkSettings();
}




void loop()
{
  Vector rawAccel = mpu.readRawAccel();
  Vector normAccel = mpu.readNormalizeAccel();
  
  /*
  Serial.print(" Xraw = ");
  Serial.print(rawAccel.XAxis);
   //delay (1000);
  
  Serial.print(" Yraw = ");
  Serial.print(rawAccel.YAxis);
    //delay (1000);
    
  Serial.print(" Zraw = ");
  Serial.println(rawAccel.ZAxis);
    //delay (1000);
   */
  Serial.print(" Xnorm = ");
  Serial.print(normAccel.XAxis);
    //delay (1000);
    
  Serial.print(" Ynorm = ");
  Serial.print(normAccel.YAxis);
    //delay (1000);
    
  Serial.print(" Znorm = ");
  Serial.println(normAccel.ZAxis);
    //delay (1000);
  float na_x_axis_kalman_degeri = GetEstimation(Xnorm_kalman_result_struct, (double) normAccel.XAxis, 0.0);
  float na_y_axis_kalman_degeri = GetEstimation(Ynorm_kalman_result_struct, (double) normAccel.YAxis, 0.0);
  float na_z_axis_kalman_degeri = GetEstimation(Znorm_kalman_result_struct, (double) normAccel.ZAxis, 0.0);

  Serial.print(" XnormKalman = ");
  Serial.print(na_x_axis_kalman_degeri);
    
  Serial.print(" YnormKalman = ");
  Serial.print(na_y_axis_kalman_degeri);
    
  Serial.print(" ZnormKalman = ");
  Serial.print(na_z_axis_kalman_degeri);
  delay(100);
}




void checkSettings()
{
  Serial.println();
  
  Serial.print(" * Sleep Mode:            ");
  Serial.println(mpu.getSleepEnabled() ? "Enabled" : "Disabled");
  
  Serial.print(" * Clock Source:          ");
  switch(mpu.getClockSource())
  {
    case MPU6050_CLOCK_KEEP_RESET:     Serial.println("Stops the clock and keeps the timing generator in reset"); break;
    case MPU6050_CLOCK_EXTERNAL_19MHZ: Serial.println("PLL with external 19.2MHz reference"); break;
    case MPU6050_CLOCK_EXTERNAL_32KHZ: Serial.println("PLL with external 32.768kHz reference"); break;
    case MPU6050_CLOCK_PLL_ZGYRO:      Serial.println("PLL with Z axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_YGYRO:      Serial.println("PLL with Y axis gyroscope reference"); break;
    case MPU6050_CLOCK_PLL_XGYRO:      Serial.println("PLL with X axis gyroscope reference"); break;
    case MPU6050_CLOCK_INTERNAL_8MHZ:  Serial.println("Internal 8MHz oscillator"); break;
  }
  
  Serial.print(" * Accelerometer:         ");
  switch(mpu.getRange())
  {
    case MPU6050_RANGE_16G:            Serial.println("+/- 16 g"); break;
    case MPU6050_RANGE_8G:             Serial.println("+/- 8 g"); break;
    case MPU6050_RANGE_4G:             Serial.println("+/- 4 g"); break;
    case MPU6050_RANGE_2G:             Serial.println("+/- 2 g"); break;
  }  

  Serial.print(" * Accelerometer offsets: ");
  Serial.print(mpu.getAccelOffsetX());
  Serial.print(" / ");
  Serial.print(mpu.getAccelOffsetY());
  Serial.print(" / ");
  Serial.println(mpu.getAccelOffsetZ());
  
  Serial.println();
}
