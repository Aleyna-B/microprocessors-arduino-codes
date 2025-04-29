// ESP32 dahili LED genellikle GPIO 2'dir
#define LED_BUILTIN 14

void setup() {
  // LED pinini çıkış olarak ayarlıyoruz
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // LED'i yak
  delay(1000);                       // 1 saniye bekle
  digitalWrite(LED_BUILTIN, LOW);    // LED'i söndür
  delay(1000);                       // 1 saniye bekle
}