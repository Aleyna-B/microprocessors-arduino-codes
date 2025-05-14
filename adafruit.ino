#include <Adafruit_NeoPixel.h> // Kütüphaneyi tanımlıyoruz
 
int led_sayisi = 8; // Kaç adet tekil LED kullandığımızı belirliyoruz
int led = 14;        // NeoPixel LED şeridin bağlı olduğu pin
int bekleme = 1000;    // Renk değişiklikleri arasındaki bekleme
int parlaklik = 50; // LED'lerin parlaklık değeri (0-255 arası)
 
Adafruit_NeoPixel serit(led_sayisi, led, NEO_GRB + NEO_KHZ800); // Tanımlamalar yapılıyor
 
void setup() {
  serit.begin();                  // Kütüphane başlatılıyor
  serit.setBrightness(parlaklik); // LED parlaklığı ayarlanıyor
}
 
void loop() {
  for(long x = 0; x < 5*65536; x += 256) {   // Kayan gökkuşağı efekti kodunun başlangıcı
    for(int y=0; y<led_sayisi; y++) {        // LED sayısına göre döngü kuruluyor
      int z = x + (y * 65536L / led_sayisi); // LED'lerin renkleri hesaplanıyor
      serit.setPixelColor(y, serit.gamma32(serit.ColorHSV(z))); // Renkler atanıyor
    }
    serit.show();   // Renkleri atanmış LED'ler yakılıyor
    delay(bekleme); // Geçişler arasındaki bekleme
  }
}