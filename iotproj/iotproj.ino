#include <Bridge.h>
#include <HttpClient.h>
#include <Process.h>


const int soundSensor = A0;
const int ledPin = 5;
const int buzzerPin = 4;
int threshold = 600;
unsigned long emergencyStartTime = 0;  
unsigned long emergencyDelay = 2000;  
bool emergencyTriggered = false; 

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
    if (emergencyStartTime == 0) 
    {
      emergencyStartTime = millis();  // Captures current time in milliseconds
      Serial.println("Threshold exceeded, starting timer...");
    }
    if (millis() - emergencyStartTime >= emergencyDelay) 
    {
      if (!emergencyTriggered) 
      {
        emergencyTriggered = true;  // Set emergency to true
        Serial.println("Emergency Detected! Siren is sustained.");
        digitalWrite(ledPin, HIGH);  
        digitalWrite(buzzerPin, HIGH);  
      }
    }
    else 
    {
      emergencyStartTime = 0;  // Reset the timer
      if (emergencyTriggered) 
      {
        emergencyTriggered = false;  // Reset emergency flag
        Serial.println("Emergency cleared.");
        digitalWrite(ledPin, LOW);  
        digitalWrite(buzzerPin, LOW);  
      }
    }  
  }

void getWeather() 
{
  HttpClient client;

  String host = "api.openweathermap.org";
  String apiKey = "efe02b156f1fe98a7b88d2547444728a";  
  String city = "Sligo,IE";
  String url = "/data/2.5/weather?q=" + city + "&appid=" + apiKey + "&units=metric";
  boolean isReading = false;
  String weatherData = "";

  String fullUrl = "http://" + host + url;
  client.get(fullUrl.c_str());
  Serial.println("Fetching weather data");

  while (client.available()) 
  {
    char c = client.read();
    weatherData += c;
    
  }
  client.stop();
}
