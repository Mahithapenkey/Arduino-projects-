void setup() {
  // put your setup code here, to run once:
  #include <LiquidCrystal.h>
#include <MQ135.h>

// LCD pin configuration
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// MQ135 Sensor Pin
#define MQ135_PIN A0

// Thresholds
#define AIR_SAFE_LEVEL 500
#define AIR_WARNING_LEVEL 1000
#define AIR_DANGER_LEVEL 2000
#define NOISE_THRESHOLD 50

// Sensor and Buzzer Pins
int soundSensorPin = A1;
int buzzerPin = 8;
int ledPin = 7;

void setup() {
  lcd.begin(16, 2); // Initialize LCD with 16x2 dimensions
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

void loop() {
  int airQuality = analogRead(MQ135_PIN);
  int noiseLevel = analogRead(soundSensorPin);

  // Convert air sensor data to PPM
  int airPPM = map(airQuality, 0, 1023, 0, 10000);
  
  // Air quality evaluation
  lcd.setCursor(0, 0);
  lcd.print("Air: ");
  if (airPPM < AIR_SAFE_LEVEL) {
    lcd.print("Fresh");
    digitalWrite(buzzerPin, LOW);
  } else if (airPPM < AIR_WARNING_LEVEL) {
    lcd.print("Poor");
    digitalWrite(buzzerPin, HIGH);
  } else {
    lcd.print("Danger");
    digitalWrite(buzzerPin, HIGH);
  }

  lcd.setCursor(0, 1);
  lcd.print("Noise: ");
  if (noiseLevel < NOISE_THRESHOLD) {
    lcd.print("Low ");
    digitalWrite(ledPin, LOW);
  } else {
    lcd.print("High");
    digitalWrite(ledPin, HIGH);
  }

  delay(1000); // Update every second
}


}

void loop() {
  // put your main code here, to run repeatedly:

}
