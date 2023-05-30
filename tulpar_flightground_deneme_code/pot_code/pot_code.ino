int i=0;
int j=0;

void setup() {

  Serial.begin(9600);

}

void loop() {
    i = analogRead(A5);
    j = analogRead(A4);
 
     if(Serial.read()=='1')
  {
    Serial.print(i);
    Serial.print("*");
    Serial.println(j); 
  } 
   delay(5);

}
