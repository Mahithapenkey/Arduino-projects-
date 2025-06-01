#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD setup (I2C address 0x27 and 16x2 characters)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin setup
const int moisturePin = A0;
const int relayPin = 8;

// Moisture threshold (tune based on your soil)
const int threshold = 600;

void setup() {
  Serial.begin(9600);
  pinMode(moisturePin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);  // Initially OFF (active LOW relay)

  // Initialize LCD
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Irrigation Sys");
  delay(2000);
  lcd.clear();
}

void loop() {
  int moistureValue = analogRead(moisturePin);
  Serial.print("Moisture: ");
  Serial.println(moistureValue);

  lcd.setCursor(0, 0);
  lcd.print("Moisture: ");
  lcd.print(moistureValue);

  if (moistureValue > threshold) {
    digitalWrite(relayPin, LOW); // Turn ON pump
    lcd.setCursor(0, 1);
    lcd.print("Pump: ON         ");
  } else {
    digitalWrite(relayPin, HIGH); // Turn OFF pump
    lcd.setCursor(0, 1);
    lcd.print("Pump: OFF        ");
  }

  delay(2000);
}

