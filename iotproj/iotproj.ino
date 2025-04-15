#include <Bridge.h>
#include <HttpClient.h>
#include <Process.h>
#include <BridgeSSLClient.h>

const int soundSensor = A0;
const int buzzer = 5;
int threshold = 600;

void setup() 
{
  Serial.begin(9600);
  while (!Serial); // Waits for serial
  
}

void loop() 
{
  
  
}
