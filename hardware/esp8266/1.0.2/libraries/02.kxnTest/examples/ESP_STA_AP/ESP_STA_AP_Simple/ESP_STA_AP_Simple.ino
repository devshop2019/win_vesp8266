//#ifdef ESP32
//#include <FS.h>
//#include <SPIFFS.h>
//#include <ESPmDNS.h>
//#include <WiFi.h>
//#include <AsyncTCP.h>
//#elif defined(ESP8266)
//#include <ESP8266WiFi.h>
//#include <ESPAsyncTCP.h>
//#include <ESP8266mDNS.h>
//#endif
//#include <ESPAsyncWebServer.h>
//#include <SPIFFSEditor.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>


const char* ssid = "AndroidAP7165";
const char* password = "1122334455";
const char * hostName = "virus";
const char* passwordHost = "12345678";

//AsyncWebServer server(80);
ESP8266WebServer server(80);

#define LED_PIN_TEST    2
unsigned long lastTimeBlinkLed = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  Serial.println("Start!");
  pinMode(LED_PIN_TEST, OUTPUT);
//  Serial.setDebugOutput(true);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(hostName, passwordHost);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("STA: Failed!\n");
    WiFi.disconnect(false);
    delay(1000);
    WiFi.begin(ssid, password);
  }

  // Bo cung được
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
  
  Serial.println(WiFi.localIP());
  server.on("/heap", []{
    server.send(200, "text/plain", String(ESP.getFreeHeap()));
  });

  server.on("/ip",[]{
    String tempData = "STA_IP: " + WiFi.localIP().toString();
    server.send(200, "text/plain", tempData);
  });
  
//  server.on("/heap", HTTP_GET, [](AsyncWebServerRequest *request){
//    request->send(200, "text/plain", String(ESP.getFreeHeap()));
//  });

//  server.on("/ip", HTTP_GET, [](AsyncWebServerRequest *request){
//    String tempData = "STA_IP: " + WiFi.localIP().toString();
//    request->send(200, "text/plain", tempData);
//  });

  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  BlinkLed();
}

void BlinkLed(){
  if(millis() - lastTimeBlinkLed >= 500){
    lastTimeBlinkLed = millis();
    digitalWrite(LED_PIN_TEST, !digitalRead(LED_PIN_TEST));
    Serial.println("Led is blinking! " + String (lastTimeBlinkLed));
  }
}
