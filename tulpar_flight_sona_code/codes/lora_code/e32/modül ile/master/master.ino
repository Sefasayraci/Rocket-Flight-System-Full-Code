#include "LoRa_E32.h"
#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(10, 11);
 
/*
   Pinler     Arduino Nano    Lora E32 433T20d
                  11                3
                  10                4
*/
 
LoRa_E32 e32ttl(&mySerial);
 
struct Signal {
  char type[15] = "Fixaj.com";
  byte temp[4];
} data;
 
 
void setup() {
  Serial.begin(9600);
  e32ttl.begin();
  delay(500);
}
 
void loop() {
 
  ResponseStatus rs = e32ttl.sendFixedMessage(0, 44, 23, &data, sizeof(Signal));
  Serial.println(rs.getResponseDescription());
 
  delay(2000);
 
  while (e32ttl.available()  > 1) {
    ResponseStructContainer rsc = e32ttl.receiveMessage(sizeof(Signal));
    struct Signal data = *(Signal*) rsc.data;
    Serial.print("Yer: ");
    Serial.println(data.type);
    Serial.print("Ortam Sıcaklığı: ");
    Serial.println(*(float*)(data.temp));
    rsc.close();
  }
}
