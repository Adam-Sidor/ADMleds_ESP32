#include <WiFi.h>
#include <FastLED.h>
#include "webConfig.h"
#include "htmlResponse.h"
#include "lightEffects.h"

#define NUM_LEDS 12  //set how many LEDs you have
#define DATA_PIN 18  //set pin where data pin is connected

WiFiServer server(80);
CRGB leds[NUM_LEDS];

short ledMode=1;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(10);
  }
  Serial.println();
  Serial.println(WiFi.localIP());
  server.begin();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}
void loop() {
  HTTPRecive();
  Serial.println(ledMode);
  if(ledMode){
    rainbowARGB(leds, NUM_LEDS);
  }else{
    FastLED.clear();
  }
  FastLED.show();
}


void HTTPRecive()
{
  WiFiClient client = server.available();
  if (client)
  {
    String currentLine = "";
    bool doonce;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        if (c == '\n')
        {
          if (currentLine.length() == 0)
          {
            sendHTMLResponse(client);
            break;
          }
          else
          {
            currentLine = "";
          }
        }
        else if (c != '\r')
        {
          currentLine += c;
        }
        if (currentLine.indexOf("/mode=") != -1)
        {
          ledMode = catchValue("/mode=",currentLine);
          doonce = 0;
        }
      }
    }
    client.stop();
    if (doonce == 0)
    {
      doonce = 1;
    }
  }
}

int catchValue(String valName,String currentLine) {
  String inputValue = "-1";
  int where=currentLine.indexOf(valName);
  if (where != -1) {
    inputValue = currentLine.substring(where+valName.length(), currentLine.length());
  }
  if(inputValue!="")
    return inputValue.toInt();
  else
   return -1;
}