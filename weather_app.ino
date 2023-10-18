#include "DHT.h"
//DHT library 

#define DHTPIN 17
//You can change the GPIO pin depending on your setup
#define DHTTYPE DHT22

//#define DHTTYPE DHT11
//Use this line of code and delete the #define DHTTYPE DHT22 if you are using a DHT11.

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(1000); //How often the measurements will be sent 

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (!isnan(h) && !isnan(t)) {
    // Send data as "humidity,temperature" with a comma separator
    Serial.print(h);
    Serial.print(",");
    Serial.println(t);
  } else {
    Serial.println("Failed to read sensor data");
    //If you get this error message check the wiring and make sure that it is the same as the one in the GitHub diagram
  }
}
