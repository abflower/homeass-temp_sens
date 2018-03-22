// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct board and BAUD rate before compiling. 

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <OneWire.h>
#include <DallasTemperature.h>
#include <CayenneMQTTESP8266.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>


// Data wire is conntec to the Arduino digital pin 2
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature sensor 

DallasTemperature DS18B20(&oneWire);

// WiFi network info.
char ssid[] = "your ssid";
char wifiPassword[] = "your pwd";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "username";
char password[] = "pwd";
char clientID[] = "client";

unsigned long lastMillis = 0;

void SetupDS18B20(){
  DS18B20.begin();
}


void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();
}

// Default function for sending sensor data at intervals to Cayenne.
CAYENNE_OUT_DEFAULT()
{
  // Write data to Cayenne here.
  DS18B20.requestTemperatures();
    //Read temperature from DS18b20
  float tempC = DS18B20.getTempCByIndex(0);
  Cayenne.celsiusWrite(1, tempC);
  //Switch wifi and wait  
  WiFi.disconnect();
  WiFi.forceSleepBegin();
  delay(60000);

  //Switch wifi on again
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, wifiPassword);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    }

  
}

// Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  //CAYENNE_LOG("Channel %u, value %s", request.channel, getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}


