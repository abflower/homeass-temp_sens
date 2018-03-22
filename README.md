# homeass-temp_sens
A temperature sensor with ESP8266-01 and DS18B20, using MQTT, in C and MicroPython - originally designed for Home Assistant, but also a version for Cayenne is available (only .ino).

In this repository you will find the code - available in C (Arduino IDE) and MicroPtyhon - for a temperature sensore built using the ESP8266-01 chip and the Dallas DS18B20 sensor, communicating over MQTT.
The are little differences between the two version but common points are:

- managing wi-fi connection
- connecting to the MQTT server
- set-up the sensor
- read and publish the value

++ MicroPython ++

Needed libraries (not included in MicroPython):
- onewire (https://github.com/micropython/micropython/tree/master/drivers/onewire)
- ds18x20 (https://github.com/micropython/micropython/tree/master/drivers/onewire)
- simple (https://github.com/micropython/micropython-lib/tree/master/umqtt.simple/umqtt)

++ C ++

Needed libraries (you can install them easily from the ARDUINO IDE)
- ESP8266WiFi.h
- PubSubClient.h
- OneWire.h
- DallasTemperature.h
