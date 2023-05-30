int tetikleme =7;

void setup() {
  // Rölenin bağlı olduğu 7 numaralı pini çıkış pini olarak ayarla
  pinMode(tetikleme,OUTPUT);
}
void loop() {
 digitalWrite(tetikleme,HIGH);  // Röleyi açık konuma getir
 delay(3000);  // 3 saniye bekle
 digitalWrite(tetikleme,LOW);  // Röleyi kapalı konuma getir
 delay(3000);  // 3 saniye bekle
}
