const int pirPin = 4;      // PIR sensor pin
const int ledPin = 5;     // LED pin

int hareket = LOW;         // Motion state
unsigned long lastMotionTime = 0; // Timestamp of the last motion detection
const unsigned long offDelay = 216000000; // Delay before turning off the LED (1 saat)

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);
  Serial.begin(9600);

  // Allow PIR sensor to stabilize
  Serial.println("PIR sensörü hazırlanıyor...");
  delay(2000); // Stabilization time
  Serial.println("PIR sensörü hazır!");
}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time
  hareket = digitalRead(pirPin);          // Read the PIR sensor

  if (hareket == HIGH) { // If motion is detected
    digitalWrite(ledPin, HIGH); // Turn on the LED
    lastMotionTime = currentMillis; // Update the timestamp of the last motion
    Serial.println("Hareket algılandı! LED açık");
  } else { // If no motion is detected
    // Check if 3 seconds have passed since the last motion
    if ((currentMillis - lastMotionTime) >= offDelay) {
      digitalWrite(ledPin, LOW); // Turn off the LED
      Serial.println("Hareket yok! LED kapalı");
    }
  }
}