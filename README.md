Emergency Service Detection with Weather and Traffic Awareness.

Description

This project detects loud levels of sound—such as from ambulance sirens or other emergency vehicles—via an analog sound sensor. Upon detection of a sound level exceeding a preconfigured threshold over an extended time frame, the system triggers an emergency alert via a buzzer and LED. In parallel, it pulls current weather data from OpenWeatherMap and can further be enhanced to encompass traffic awareness to help decide whether the detected siren can be delayed or impeded by conditions.

Features

1. Real-time sound detection triggering based on threshold.

2. Emergency alarm system comprising buzzer and LED indicator.

3. Live weather fetch from OpenWeatherMap for a specified city (e.g., Sligo, IE).

Potential traffic extension

information: weather and traffic information inform understanding of environment in relation to emergency sounds.

Adjustment of sound threshold and trigger duration for personalization.

Parts Needed

1x Arduino board (e.g., Arduino Yun)
1x Analog sound sensor
1x Buzzer
1x LED
1x Base shield
Internet access (through Bridge or Ethernet Shield)


Sound Sensor: Analog output to A0.
LED: Pin 5,
Buzzer: Pin 4, 

Code Explanation

Detection of sound
Reads analog values continuously from the sound sensor.
If crossing the threshold is exceeded for more than 2 seconds (configurable), an emergency is activated.
Emergency Trigger
Activates a buzzer and LED to signal the occurrence.
Gets weather conditions to analyze external conditions.
Weather Integration
Connects to OpenWeatherMap API to retrieve live weather.
Displays the weather description (e.g., "clear sky", "rain") via serial monitor.

Optional Traffic Data (Extension Idea)
Add a traffic API to determine if detected sirens correlate with congested routes.
Beneficial in city areas where response time in case of emergencies may be affected.

Reset Condition

When the sound falls below the threshold or fails to meet the duration, the system resets.
