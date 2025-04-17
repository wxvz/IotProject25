#include <Bridge.h>
#include <HttpClient.h>
#include <Process.h>


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
    Serial.println("Alert! Siren detected!");
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
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

  client.get(host, 80, url);
  Serial.println("Fetching weather data");

  
}
