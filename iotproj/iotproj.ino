#include <ArduinoJson.h>
#include <Bridge.h>
#include <HttpClient.h>
#include <Process.h>

const int sampleCount = 100;
int noiseBaseline = 0;
const int soundSensor = A0;
const int ledPin = 5;
const int buzzerPin = 4;
unsigned long emergencyStartTime = 0;  
unsigned long emergencyDelay = 1300;  
bool emergencyTriggered = false;
String weatherDescription = ""; 

void setup() 
{
  Serial.begin(9600);
  while (!Serial); // Waits for serial
  Serial.println("Starting");
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
        sendSMS();
        delay(300000);
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
  String apiKey = "b9e09a2989cabb7220b2a80a07b2a320";  
  String lat = "54.26969";  
  String lon = "-8.46943";
  String url = "/data/2.5/forecast?lat=" + lat + "&lon=" + lon + "&appid=" + apiKey + "&units=metric";
  String fullUrl = "http://" + host + url;

  Serial.println("Fetching weather data...");

  int statusCode = client.get(fullUrl.c_str());

  if (statusCode != 200) 
  {
    Serial.print("HTTP request failed. Status code: ");
    Serial.println(statusCode);
    return;
  }

  String weatherData = "";
  while (client.available()) 
  {
    char c = client.read();
    weatherData += c;
    
  }

  // Parse the received JSON data
  StaticJsonDocument<4096> doc;
  DeserializationError error = deserializeJson(doc, weatherData);

  if (error) 
  {
    Serial.print("Failed to parse JSON: ");
    Serial.println(error.f_str());
    return;
  }

  // Extract weather description from the JSON response
  weatherDescription = doc["list"][0]["weather"][0]["description"].as<String>();
  Serial.print("Weather Description: ");
  Serial.println(weatherDescription);

  // Display the weather description on the serial monitor
  Serial.println("Weather fetched during emergency.");
}

int calculatingBackgroundNoise() 
{
  const int sampleCount = 100;
  long total = 0;
  
  for (int i = 0; i < sampleCount; i++) 
  {
    total += analogRead(soundSensor);
    delay(10);
  }

  noiseBaseline = total / sampleCount;
  int calibratedThreshold = noiseBaseline + 100; 

  Serial.print("Current Threshold: ");
  Serial.println(calibratedThreshold);

  return calibratedThreshold;
}

void sendSMS() 
{
  String accountSID = "AC0ce3081a8990b9984552ecbb0ea9a2e4";  
  String authToken = "eb72b60baed788ef633ec3ce72965af8";  
  
  // Construct the curl command to send the SMS
  String cmd = "curl -X POST 'https://api.twilio.com/2010-04-01/Accounts/" + accountSID + "/Messages.json' "
             "--data-urlencode 'To=+353857719256' "
             "--data-urlencode 'From=+13512004533' "
             "--data-urlencode 'Body=EMERGENCY VEHICLE APPROACHING!! MAKE WAY.' "
             "-u " + accountSID + ":" + authToken;
                  
  Serial.println("Sending SMS...");
  
  Process p;
  p.runShellCommand(cmd);  // Execute the curl command
  
  while (p.running());  // Wait for the process to finish
  while (p.available()) {
    char c = p.read();  
    Serial.print(c);
  }
}
