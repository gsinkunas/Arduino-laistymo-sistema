// Arduino-based irrigation system for greenhouse with soil moisture sensor and pump control.

const int pumpPin = 4;          // Controls MOSFET gate for the pump
const int sensorPowerPin = 5;   // Powers the moisture sensor
const int sensorPin = 6;        // Reads digital output from the moisture sensor

const unsigned long pumpRunTime = 5000;    // Pump run time in milliseconds
const unsigned long readingInterval = 60000; // Time between moisture checks in milliseconds

void setup() {
  pinMode(pumpPin, OUTPUT);
  digitalWrite(pumpPin, LOW); // Ensure pump is off

  pinMode(sensorPowerPin, OUTPUT);
  digitalWrite(sensorPowerPin, LOW); // Sensor off by default to reduce corrosion

  pinMode(sensorPin, INPUT);
}

void loop() {
  // Power on the moisture sensor
  digitalWrite(sensorPowerPin, HIGH);
  delay(10); // Allow sensor to stabilize

  int moistureState = digitalRead(sensorPin);

  // Power off the sensor after reading
  digitalWrite(sensorPowerPin, LOW);

  // For LM393-based sensors: HIGH = dry, LOW = wet (adjust as needed)
  if (moistureState == HIGH) {
    digitalWrite(pumpPin, HIGH); // Activate pump
    delay(pumpRunTime);
    digitalWrite(pumpPin, LOW);  // Deactivate pump
  }

  delay(readingInterval);
}
