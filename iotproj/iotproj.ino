#include <Bridge.h>
#include <HttpClient.h>
#include <Process.h>
#include <BridgeSSLClient.h>

const int soundSensor = A0;
const int ledPin = 5;
const int buzzerPin = 4;
int threshold = 600;

void setup() 
{
  Serial.begin(9600);
  while (!Serial); // Waits for serial
  Bridge.begin();
  Serial.println("Bridge initialized.");
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() 
{
  int soundLevel = analogRead(soundSensor);
  Serial.print("Sound Level: ");
  Serial.println(soundLevel);

  if (soundLevel > threshold) 
  {
    Serial.println("🚨 Siren detected!");
    digitalWrite(led, HIGH);
    digitalWrite(buzzerPin, HIGH);
    
  }
}
