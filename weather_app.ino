#include "DHT.h"

#define DHTPIN 17
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(1000); // Increase the delay to ensure stable readings

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed reception");
    return;
  }

  // Serial.print("Humidity: ");
  // Serial.print(h);
  // Serial.print("%, ");
  // Serial.print("Temperature: ");
  // Serial.print(t);
  // Serial.println("°C");

  // Send data as "humidity,temperature" with a comma separator
  Serial.print(h);
  Serial.print(",");
  Serial.print(t);
  Serial.println();
}
