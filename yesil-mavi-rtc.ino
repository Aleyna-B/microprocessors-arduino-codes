#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <Adafruit_NeoPixel.h>

// ================ PIN CONFIGURATIONS =================
#define DS1302_CE_PIN   4    // RST pin of DS1302
#define DS1302_IO_PIN    19   // DAT pin
#define DS1302_SCLK_PIN 18    // SCLK pin
#define NEOPIXEL_PIN    14    // Single NeoPixel RGB LED
#define NEOPIXEL_COUNT  8     // Just one LED
// ====================================================

// Create DS1302 object
ThreeWire myWire(DS1302_IO_PIN, DS1302_SCLK_PIN, DS1302_CE_PIN); // Fixed pin order
RtcDS1302<ThreeWire> rtc(myWire);

// Create NeoPixel object
Adafruit_NeoPixel strip =
  Adafruit_NeoPixel(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

void printDateTime(const RtcDateTime& dt) {
  char datestring[20];
  snprintf_P(datestring, 
             sizeof(datestring),
             PSTR("%02u:%02u:%02u"),
             dt.Hour(),
             dt.Minute(),
             dt.Second());
  Serial.println(datestring);
}

void setup() {
  Serial.begin(921600);
  Serial.println("Initializing...");
  
  // Initialize NeoPixel
  strip.begin();
  strip.show(); // Turn off all pixels initially
  
  // Initialize DS1302 RTC
  rtc.Begin();
  
  if (!rtc.IsDateTimeValid()) {
    Serial.println("RTC has invalid time, correcting...");
    
    if (rtc.GetIsWriteProtected()) {
      rtc.SetIsWriteProtected(false);
      Serial.println("RTC write protection disabled");
    }
    
    if (!rtc.GetIsRunning()) {
      rtc.SetIsRunning(true);
      Serial.println("RTC started");
    }
    
    // Optional: Set time once (uncomment to use)
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    rtc.SetDateTime(compiled);
    Serial.println("RTC time set to compilation time");
  }
  
  if (!rtc.IsDateTimeValid()) {
    Serial.println("WARNING: RTC time still not valid!");
  } else {
    Serial.println("RTC ready");
  }
}

void loop() {
  if (!rtc.IsDateTimeValid()) {
    // Don't rely on potentially incorrect readings
    Serial.println("RTC lost confidence in the DateTime!");
    strip.setPixelColor(0, strip.Color(255, 0, 0)); // Red indicates error
    strip.show();
    delay(1000);
    return;
  }
  
  RtcDateTime now = rtc.GetDateTime(); // Get current time
  
  // Print current time to serial monitor with proper formatting
  printDateTime(now);
  
  // Set NeoPixel color based on even or odd second
  if (now.Second() % 2 == 0) {
    strip.setPixelColor(0, strip.Color(0, 0, 255)); 
  } else {
    strip.setPixelColor(0, strip.Color(0, 255, 0)); 
  }
  
  strip.show(); // Update LED
  
  delay(600); // Wait a second before next read
}