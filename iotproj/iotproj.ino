#include <ArduinoJson.h>
#include <Bridge.h>
#include <HttpClient.h>

const int sampleCount = 100;
int noiseBaseline = 0;
const int soundSensor = A0;
const int ledPin = 5;
const int buzzerPin = 4;
unsigned long emergencyStartTime = 0;  
unsigned long emergencyDelay = 800;  
bool emergencyTriggered = false;
String weatherDescription = ""; 

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
  int threshold = calculatingBackgroundNoise();
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
      unsigned long timeElapsed = millis() - emergencyStartTime;
      Serial.print("Waiting... ");
      Serial.print(timeElapsed);
      Serial.println(" ms so far.");

      if (timeElapsed >= emergencyDelay && !emergencyTriggered) 
      {
        emergencyTriggered = true;  // Set emergency to true
        Serial.println("Emergency Detected! Siren is sustained.");
        digitalWrite(ledPin, HIGH);  
        digitalWrite(buzzerPin, HIGH);
        getWeather();  
        Serial.print("Weather Description: ");
        Serial.println(weatherDescription);  
      }
    }
    else 
    {
      Serial.println("Waiting... sustained sound not long enough.");
    } 
  }
  else 
  {
    if (emergencyStartTime != 0) 
    {
      Serial.println("Sound dropped below threshold. Resetting timer.");
    } 
    emergencyStartTime = 0;  // Reset the timer
    
    if (emergencyTriggered) 
    {
      emergencyTriggered = false;  // Reset emergency condition
      Serial.println("Emergency cleared.");
      digitalWrite(ledPin, LOW);  
      digitalWrite(buzzerPin, LOW);  
      Serial.println("Emergency cleared due to sound drop.");
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
    Serial.print(c); // For testing 
  }
  
  const size_t capacity = 1024;
  StaticJsonDocument<1024> doc;
  DeserializationError error = deserializeJson(doc, weatherData);

  if (error) 
  {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.f_str());
    return;  // Exit if there is a problem parsing
  }
  weatherDescription = doc["weather"][0]["description"].as<String>();  
  Serial.print("Weather Description: ");
  Serial.println(weatherDescription);
}

int calculatingBackgroundNoise() 
{
  const int sampleCount = 100;
  long total = 0;
  
  for (int i = 0; i < sampleCount; i++) 
  {
    total += analogRead(soundSensor);
    delay(5);
  }

  int noiseBaseline = total / sampleCount;
  int calibratedThreshold = noiseBaseline + 100; 

  Serial.print("Current Threshold: ");
  Serial.println(calibratedThreshold);

  return calibratedThreshold;
}
