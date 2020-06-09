#include "DHT.h"

#define DHTPIN 2
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

#include "Arduino.h"
#include "LTimer.h"
DHT dht(DHTPIN, DHTTYPE);
LTimer timer0(LTIMER_0);
float h,t,f,hic,hif;
void _callback0(void *usr_data) 
{ Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("'C "));
  Serial.print(f);
  Serial.print(F("'F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("'C "));
  Serial.print(hif);
  Serial.println(F("'F"));
  }
void setup() {
  Serial.begin(9600);
  timer0.begin();
  Serial.println(F("DHTxx test!"));

  dht.begin();
  timer0.start(1000, LTIMER_REPEAT_MODE, _callback0, NULL); 
}

void loop() {
  
   h = dht.readHumidity();
  // Read temperature as Celsius (the default)
   t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
   f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
   hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
   hic = dht.computeHeatIndex(t, h, false);

 
}

