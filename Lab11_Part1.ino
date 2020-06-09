#include <LWiFi.h>
#include "MCS.h"
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
char _lwifi_ssid[] = "YTY";
char _lwifi_pass[] = "12345678";
MCSDevice mcs("Dx8uWn6K", "GuVu84Dq7DEjK0J6");

MCSDisplayFloat  Temperature("temp");
MCSDisplayFloat  Humidity("humi");
void setup()
{
  dht.begin();
  Serial.begin(9600);
  Serial.println("Connect to Wifi");
  while (WiFi.begin(_lwifi_ssid, _lwifi_pass) != WL_CONNECTED) {
    Serial.println("Wifi Reconnecting..");
    delay(1000);
  }

  Serial.println("Connect to MCS...");
  while (!mcs.connected()) {
    Serial.println("MCS Reconnecting..");
    mcs.connect();
  }
  Serial.println("MCS Connected!");
  Serial.println("Humidity and temperature\n\n");
  mcs.addChannel(Temperature);
  mcs.addChannel(Humidity);
}


void loop()
{
  while (!mcs.connected()) {
    mcs.connect();
    if (mcs.connected()) {
      Serial.println("MCS Reconnect");
    }
  }
  mcs.process(1000);
 float h = dht.readHumidity();
  float t = dht.readTemperature();
   if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
   Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Humidity.set(h);
  Temperature.set(t);
  Serial.println("Add sensor value.");
  delay(200);
}

