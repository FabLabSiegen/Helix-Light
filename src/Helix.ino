#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ArduinoOTA.h>
#include <NeoPixelBus.h>

const uint16_t PixelCount = 6;
const float S = 1.0f;
const float B = 1.0f;
const int delayTime = 15; //ms

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount);

int counter = 0;
int colorStep = 1000/PixelCount;

const char* password = "Helix"; // CHANGE THIS!

void setup() 
{
  strip.Begin();
  strip.Show();
  
  for(int i = 0; i < PixelCount; i++)
  {
    strip.SetPixelColor(i,HsbColor(0,S,B)); // set all pixel to red
  }
  strip.Show();
  
  WiFiManager wifiManager;
  wifiManager.setTimeout(120);
  wifiManager.autoConnect("Helix");
  
  ArduinoOTA.setHostname("Helix");
  ArduinoOTA.setPassword(password); 
  ArduinoOTA.begin();
}

void loop() 
{
  int tmp = 0;
  
  ArduinoOTA.handle();
  
  counter = (++counter)%1001;
  
  for(int i = 0; i < PixelCount; i++)
  {
    tmp = (counter+(colorStep*i))%1001; 
    strip.SetPixelColor(i,HsbColor(tmp/1000.0,S,B)); // set the leds to different colors on the color circle, see https://github.com/Makuna/NeoPixelBus/wiki/HsbColor-object-API
  }

  strip.Show();
  delay(delayTime);
}
