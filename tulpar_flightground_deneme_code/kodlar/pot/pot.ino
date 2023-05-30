/*
//#define potpin A5
int i = 0;

void setup() {
  Serial.begin(9600);
  //Serial.println("Pot Deger Okuma");
}
void loop() {
   i = analogRead (A5);
  if (Serial.read()=="1"){
      Serial.println(i);
  }
   delay(100);
}
*/
/*
//#define potpin A5
int deger = 0; 
void setup() {
  Serial.begin(9600);
 // Serial.println("Pot Deger Okuma");
}
void loop() {
  deger = analogRead(A5);

  if (Serial.read()=="1"){
     Serial.println(deger);
  }

  delay(100); 
}
*/

int i;
void setup() 
{
  Serial.begin(9600);
}
void loop() 
{
  i=analogRead(A0);
  if(Serial.read()==1)
  {
    Serial.println(i);
    delay(5);
  }
}
