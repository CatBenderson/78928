#include <WiFi.h>
const char* ssid="dr-rojano";
const char* password="78928-tw";

void setup() {
  Serial.begin(115200);
  delay(10);
  
  //Se inicia la conexión
  Serial.println();
  Serial.println();
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);

  //se verifica la conexión
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  //Lograda la conexión se muestra la información
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

}
