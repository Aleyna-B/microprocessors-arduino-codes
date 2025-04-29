#include <ThreeWire.h>  
#include <RtcDS1302.h>

// ESP32 pins (change as needed)
#define PIN_CLK  18
#define PIN_DAT  19
#define PIN_RST  4

ThreeWire myWire(PIN_DAT, PIN_CLK, PIN_RST); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
  Serial.begin(921600);
  Rtc.Begin();

  // Uncomment this block only once to set time
  /*
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Rtc.SetDateTime(compiled);
  */

  if (!Rtc.IsDateTimeValid()) {
    Serial.println("RTC lost confidence in the DateTime!");
  }
}

void loop() {
  RtcDateTime now = Rtc.GetDateTime();

  Serial.print("Date: ");
  Serial.print(now.Day());
  Serial.print("/");
  Serial.print(now.Month());
  Serial.print("/");
  Serial.print(now.Year());

  Serial.print(" Time: ");
  Serial.print(now.Hour());
  Serial.print(":");
  Serial.print(now.Minute());
  Serial.print(":");
  Serial.println(now.Second());

  delay(500);
}
