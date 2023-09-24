#include "DHT.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HTTPClient.h>
#include <UrlEncode.h>

#define DHTPIN 17
#define DHTTYPE DHT22
//DHTTYPE = DHT11, but there are also DHT22 and 21



// const char* ssid = "Telstra616345";
// const char* password = "jq92mnfwc8";


const char* ssid = "CC-Ext";
const char* password = "CCRasPiNetwork";

WebServer server(80);
DHT dht(DHTPIN, DHTTYPE); // constructor to declare our sensor

// void setup() {
//   Serial.begin(115200);
//   dht.begin();
// }

void handleRoot() {
  char msg[1500];

  snprintf(msg, 1500,
           "<html>\
  <head>\
    <meta http-equiv='refresh' content='4'/>\
    <meta name='viewport' content='width=device-width, initial-scale=1'>\
    <link rel='stylesheet' href='https://use.fontawesome.com/releases/v5.7.2/css/all.css' integrity='sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr' crossorigin='anonymous'>\
    <title>ESP32 DHT Server</title>\
    <style>\
    html { font-family: Arial; display: inline-block; margin: 0px auto; text-align: center;}\
    h2 { font-size: 3.0rem; }\
    p { font-size: 3.0rem; }\
    .units { font-size: 1.2rem; }\
    .dht-labels{ font-size: 1.5rem; vertical-align:middle; padding-bottom: 15px;}\
    </style>\
  </head>\
  <body>\
      <h2>ESP32 DHT Server!</h2>\
      <p>\
        <i class='fas fa-thermometer-half' style='color:#ca3517;'></i>\
        <span class='dht-labels'>Temperature</span>\
        <span>%.2f</span>\
        <sup class='units'>&deg;C</sup>\
      </p>\
      <p>\
        <i class='fas fa-tint' style='color:#00add6;'></i>\
        <span class='dht-labels'>Humidity</span>\
        <span>%.2f</span>\
        <sup class='units'>&percnt;</sup>\
      </p>\
  </body>\
</html>",
           readDHTTemperature(), readDHTHumidity()
          );
  server.send(200, "text/html", msg);
}

void setup(void) {

  Serial.begin(115200);
  dht.begin();
 
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }
  server.on("/", handleRoot);

  server.begin();
  Serial.println("HTTP server started");

}

void loop(void) {
  server.handleClient();
  delay(2);//allow the cpu to switch to other tasks

}


// void loop() {
//   delay(1000);
//   // The DHT11 returns at most one measurement every 1s
//   //Read the moisture content in %.
//   //Read the temperature in degrees Celsius

//   if (isnan(h) || isnan(t)) {
//     Serial.println("Failed reception");
//     return;
//     //Returns an error if the ESP32 does not receive any measurements
//   }

  float readDHTHumidity() {
      float h = dht.readHumidity();
      if (isnan(h)) {
        Serial.println("Failed reception");
        return -1;
      } 
      else{
        // Serial.print(h);
        Serial.print("Humidite: ");
        Serial.println(h);
        Serial.print("%");
        if(h>=70){
          sendMessage("Humidity is above 70%");
        }
        return h;
        
      }
    }
  
  

  float readDHTTemperature() {
    float t = dht.readTemperature();
      if (isnan(t)) {
        Serial.println("Failed reception");
        return -1;
      }
      else{
        Serial.print("Temperature: ");
        Serial.println(t);
        Serial.print("°C");

        if(t>=25){
          sendMessage("Temperature is above 25 degrees! Turn on the air conditioner!!!!!!");
        }
        Serial.print("°C, ");
        return t;
      }
    }


String phoneNumber = "+61414964306";
String apiKey = "1163640";

void sendMessage(String message){

  // Data to send with HTTP POST
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);    
  HTTPClient http;
  http.begin(url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}





  // Serial.print("Humidite: ");
  // Serial.print(h);
  // Serial.print("%  Temperature: ");
  // Serial.print(t);
  // Serial.print("°C, ");

  // Transmits the measurements received in the serial monitor
