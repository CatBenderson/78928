#include <WiFi.h>
#include <ESPAsyncWebSrv.h>
const char *ssid = "OPPO A54";
const char *password = "ranita321";
AsyncWebServer server(80);

void setup() {
  Serial.begin(115200);
  // delay(10);
  conectarse();
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    int numParametros = request->params();
    Serial.print(numParametros);
    if (numParametros == 0) 
    request->send(200, "text/html", "<H1>Hola Mundo</H1>");
    else {
      AsyncWebParameter *p = request->getParam(0);
      String html = "<H1>Hola " + p->value() + "</H1>";
      request->send(200, "text/html", html);
    }
  });
  server.on("/adios", HTTP_GET, [](AsyncWebServerRequest *r) {
    r->send(200, "text/html", "<h1>adios</h1>");
  });
  
  pinMode(2, OUTPUT);

  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *r) {
    r->send(200, "text/html", "<h1>on</h1>");
    digitalWrite(2, HIGH);
  });

  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *r) {
    r->send(200, "text/html", "<h1>off</h1>");
    digitalWrite(2, LOW);
  });

  
  server.begin();
  Serial.println();
}


void loop() {}

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