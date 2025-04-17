Sound Level Detection with Emergency Alert and Weather Fetching

Description

This project detects high sound levels using an analog sound sensor, triggers an emergency alarm (LED and buzzer) if the sound exceeds a threshold for a certain period, and fetches weather data from OpenWeatherMap. The weather description (such as "clear sky", "cloudy", etc.) is then displayed on the serial monitor.

Features:
Sound detection with threshold-based triggering.
Emergency alert with a buzzer and LED.
Fetching weather data from OpenWeatherMap based on a city (Sligo, IE in this case).
Adjustable sound threshold and delay for emergency trigger.
Components Needed

Arduino board (e.g., Arduino Yun)
Sound sensor
Buzzer
LED
Jumper wires
Internet connection for weather fetching (requires bridge or Ethernet shield)
Circuit

Sound Sensor: Connect the analog output of the sound sensor to A0 on the Arduino.
LED: Connect the positive leg (longer leg) to Pin 5 and the negative leg to ground.
Buzzer: Connect the positive leg to Pin 4 and the negative leg to ground.
