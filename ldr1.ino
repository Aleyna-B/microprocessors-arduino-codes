#include <Adafruit_NeoPixel.h>

#define LDR_PIN 32         // LDR bağlı pin
#define LED_PIN 14         // NeoPixel veri pini
#define NUM_LEDS 8         // LED sayısı

Adafruit_NeoPixel leds(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  leds.begin();           // LED şeridini başlat
  leds.show();            // Tüm LED'leri kapat (ilk durum)
}

void loop() {
  int ldr_degeri = analogRead(LDR_PIN); // 0-4095 arası okuma
  Serial.print("LDR Işık Seviyesi: ");
  Serial.println(ldr_degeri);

  if (ldr_degeri < 3000) {
    // 8 LED'in hepsini beyaz yak
    for (int i = 0; i < NUM_LEDS; i++) {
      leds.setPixelColor(i, leds.Color(255, 255, 255)); // R, G, B
    }
  } else {
    // Işık yeterliyse LED'leri kapat
    for (int i = 0; i < NUM_LEDS; i++) {
      leds.setPixelColor(i, 0); // LED kapalı
    }
  }
  leds.show(); // Değişiklikleri uygula

  delay(500);  // 0.5 saniye bekle
}

