const int sensorPin = A0;
const int ledPin = 5;
int sensorValue = 0;
int ledBrightness = 0;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  Serial.print("Light Sensor Value: ");
  Serial.println(sensorValue);

  if (sensorValue < 100) {
    ledBrightness = 255;  // Fully bright in darkness
  } else if (sensorValue > 900) {
    ledBrightness = 0;  // Turn off in full brightness
  } else {
    ledBrightness = map(sensorValue, 100, 900, 255, 0);
  }

  analogWrite(ledPin, ledBrightness);
  
  Serial.print("LED Brightness: ");
  Serial.println(ledBrightness);
  
  delay(500);
}