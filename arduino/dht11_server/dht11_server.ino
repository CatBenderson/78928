#include "DHTesp.h"
#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
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
    String html = "<H1>Humedad: " + String(humedad) + "°</H1>";
    r->send(200, "text/html", html);
  });

  server.on("/centigrados", HTTP_GET, [](AsyncWebServerRequest *r) {
    float temperatura=dht.getTemperature();
    String html = "<H1>Temperatura(C): " + String(temperatura) + "°</H1>";
    r->send(200, "text/html", html);
  });

  server.on("/fahrenheit", HTTP_GET, [](AsyncWebServerRequest *r) {
    float temperatura=dht.toFahrenheit(dht.getTemperature());
    String html = "<H1>Temperatura(F): " + String(temperatura) + "°</H1>";
    r->send(200, "text/html", html);
  });

  server.on("/indiceCalorC", HTTP_GET, [](AsyncWebServerRequest *r) {
    float temperatura=dht.computeHeatIndex(dht.getTemperature(), dht.getHumidity(), false);
    String html = "<H1>Indice Calor(C): " + String(temperatura) + "°</H1>";
    r->send(200, "text/html", html);
  });

  server.on("/indiceCalorF", HTTP_GET, [](AsyncWebServerRequest *r) {
    float temperatura=dht.computeHeatIndex(dht.toFahrenheit(dht.getTemperature()), dht.getHumidity(), true);
    String html = "<H1>Indice Calor(F): " + String(temperatura) + "°</H1>";
    r->send(200, "text/html", html);
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