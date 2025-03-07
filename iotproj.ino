const int sensorPin = A0; //Light Sensor on A0
const int ledPin = 5; //LED on Digital Pin 5
int sensorValue = 0;
int ledBrightness = 0;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  sensorValue = analogRead(sensorPin); //Reads in light sensor value.
  Serial.print("Light Intensity: ");
  Serial.println(sensorValue); //Prints Light Intensiy/Value.

  ledBrightness = map(sensorValue, 0, 1023, 255, 0); //inverts brightness. more light when darker.
  analogWrite(ledPin, ledBrightness); //controls the brightness
  
  Serial.print("LED Brightness: ")
  Serial.println(ledBrightness);

  delay(500);
  
}
