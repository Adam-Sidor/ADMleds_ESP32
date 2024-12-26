#include <WiFi.h>
#include <FastLED.h>
#include "webConfig.h"
#include "htmlResponse.h"
#include "lightEffects.h"

#define NUM_LEDS 35  //set how many LEDs you have
#define DATA_PIN 18  //set pin where data pin is connected

WiFiServer server(80);
CRGB leds[NUM_LEDS];

CRGB ledsColor(0,0,0);

short ledMode=0;
bool ledStatus=true,isNightModeOn;
uint8_t brightness=255,nightModeBrighness=16;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //set your WiFi settings
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
  if(ledStatus){
    if(isNightModeOn)
      FastLED.setBrightness(nightModeBrighness);
    else
      FastLED.setBrightness(brightness);
    switch (ledMode) {
    case 0:
      rainbowARGB(leds, NUM_LEDS);
      break;
    case 1:
      rainbowRGB(leds,NUM_LEDS,10);
      break;
    case 2:
      setColor(leds,NUM_LEDS,ledsColor);
      break;
    case 3:
      thunder(leds,NUM_LEDS,ledsColor,250);
      break;
    default:
      FastLED.clear();
  }
  }else{
    FastLED.setBrightness(0);
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
        if (currentLine.indexOf("/status=") != -1)
        {
          ledStatus = catchValue("/status=",currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/brightness=") != -1)
        {
          brightness = catchValue("/brightness=",currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/nightmode=") != -1)
        {
          isNightModeOn = catchValue("/nightmode=",currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/nightbrightness=") != -1)
        {
          nightModeBrighness = catchValue("/nightbrightness=",currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/r=") != -1)
        {
          ledsColor.r = catchValue("/r=",currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/g=") != -1)
        {
          ledsColor.g = catchValue("/g=",currentLine);
          doonce = 0;
        }
        if (currentLine.indexOf("/b=") != -1)
        {
          ledsColor.b = catchValue("/b=",currentLine);
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