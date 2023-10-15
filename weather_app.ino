#include "DHT.h"

#define DHTPIN 17
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(1000); // Increased delay for more stable readings (adjust as needed)

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (!isnan(h) && !isnan(t)) {
    // Send data as "humidity,temperature" with a comma separator
    Serial.print(h);
    Serial.print(",");
    Serial.println(t);
  } else {
    Serial.println("Failed to read sensor data");
  }
}
