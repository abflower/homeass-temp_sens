// Libraries

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define wifi_ssid "yous ssid"
#define wifi_password "your pwd"
#define mqtt_server "server IP"
#define mqtt_user "user"
#define mqtt_password "pwd mqtt"
#define temperature_topic "sensor/temperature"

//Setup sensor
// Data wire is connteced to pin 2
#define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature sensor 
DallasTemperature DS18B20(&oneWire);

WiFiClient espClient;
PubSubClient client(espClient);



//unsigned long lastMillis = 0;

void setup(){
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  DS18B20.begin();
}

void setup_wifi() {
  delay(10);
  Serial.print("Connecting to WLAN");
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  }
  Serial.print("Connected to WLAN");
}


void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    // If you do not want to use a username and password, change next line to
    // if (client.connect("ESP8266Client")) {
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected to MQTT");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  DS18B20.requestTemperatures();
  float temp = DS18B20.getTempCByIndex(0);
  Serial.print("New temperature:");
  Serial.println(String(temp).c_str());
  client.publish(temperature_topic, String(temp).c_str(), true);
  delay(600000); //wait 10 minute
}


