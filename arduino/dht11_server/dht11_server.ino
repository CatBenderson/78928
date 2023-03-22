#include "DHTesp.h"
#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
#include <ArduinoJson.h>
#define DHTpin 15
DHTesp dht;
const char *ssid = "OPPO A54";
const char *password = "ranita321";
AsyncWebServer server(80);


void setup(){
  Serial.begin(115200);
  conectarse();
  Serial.println();
  dht.setup(DHTpin, DHTesp::DHT11);

  server.on("/humedad", HTTP_GET, [](AsyncWebServerRequest *r) {
    float humedad= dht.getHumidity();
    AsyncResponseStream *response = r->beginResponseStream("application/json");
    DynamicJsonDocument json(1024);
    json["humedad"]=humedad;
    serializeJson(json, *response);
    response->addHeader("Access-Control-Allow-Origin", "*");
    r->send(response);
    //String html = "<H1>Humedad: " + String(humedad) + "°</H1>";
  });

  server.on("/centigrados", HTTP_GET, [](AsyncWebServerRequest *r) {
    float temperatura=dht.getTemperature();
    AsyncResponseStream *response = r->beginResponseStream("application/json");
    DynamicJsonDocument json(1024);
    json["centigrados"]=temperatura;
    serializeJson(json, *response);
    response->addHeader("Access-Control-Allow-Origin", "*");
    r->send(response);
  });

  server.on("/fahrenheit", HTTP_GET, [](AsyncWebServerRequest *r) {
    float temperatura=dht.toFahrenheit(dht.getTemperature());
    AsyncResponseStream *response = r->beginResponseStream("application/json");
    DynamicJsonDocument json(1024);
    json["fahrenheit"]=temperatura;
    serializeJson(json, *response);
    response->addHeader("Access-Control-Allow-Origin", "*");
    r->send(response);
  });

  server.on("/indiceCalorC", HTTP_GET, [](AsyncWebServerRequest *r) {
    float indiceCalorC=dht.computeHeatIndex(dht.getTemperature(), dht.getHumidity(), false);
    AsyncResponseStream *response = r->beginResponseStream("application/json");
    DynamicJsonDocument json(1024);
    json["indiceCalorC"]=indiceCalorC;
    serializeJson(json, *response);
    response->addHeader("Access-Control-Allow-Origin", "*");
    r->send(response);
  });

  server.on("/indiceCalorF", HTTP_GET, [](AsyncWebServerRequest *r) {
    float indiceCalorF=dht.computeHeatIndex(dht.toFahrenheit(dht.getTemperature()), dht.getHumidity(), true);
    AsyncResponseStream *response = r->beginResponseStream("application/json");
    DynamicJsonDocument json(1024);
    json["indiceCalorF"]=indiceCalorF;
    serializeJson(json, *response);
    response->addHeader("Access-Control-Allow-Origin", "*");
    r->send(response);
  });

  server.begin();
}

void loop(){}

void conectarse() {
  Serial.print("Conectando ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print(WiFi.localIP());
}