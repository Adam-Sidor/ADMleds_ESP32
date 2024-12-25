#include <WiFi.h>
#include "webConfig.h"

WiFiServer server(80);
void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(10);
  }
  Serial.println();
  Serial.println(WiFi.localIP());
}

void loop() {
  

}
