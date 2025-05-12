#include <Adafruit_NeoPixel.h>

#define LDR_PIN 32         // LDR bağlı pin
#define LED_PIN 14         // NeoPixel veri pini
#define NUM_LEDS 8         // LED sayısı

Adafruit_NeoPixel leds(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  leds.begin();
  leds.show(); // LED'leri başlangıçta kapat
}

void loop() {
  int ldr_degeri = analogRead(LDR_PIN); // 0-4095
  Serial.print("LDR Işık Seviyesi: ");
  Serial.println(ldr_degeri);

  // LDR değeri 0 (karanlık) - 4095 (çok aydınlık)
  // Ters orantılı parlaklık: ışık azalınca parlaklık artsın
  int parlaklik = map(ldr_degeri, 0, 4095, 255, 0); // 255 (max) - 0 (kapalı)

  // Renk geçişi: düşük ışıkta beyaz, orta ışıkta sarı, yüksek ışıkta kapalı
  uint8_t r, g, b;

  if (ldr_degeri < 1500) {
    // Karanlık: beyaz
    r = g = b = parlaklik;
  } else if (ldr_degeri < 3000) {
    // Orta seviye ışık: sarı-turuncu
    r = parlaklik;
    g = parlaklik / 2;
    b = 0;
  } else {
    // Çok aydınlık: LED kapalı
    r = g = b = 0;
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds.setPixelColor(i, leds.Color(r, g, b));
  }
  leds.show();

  delay(500);
}

