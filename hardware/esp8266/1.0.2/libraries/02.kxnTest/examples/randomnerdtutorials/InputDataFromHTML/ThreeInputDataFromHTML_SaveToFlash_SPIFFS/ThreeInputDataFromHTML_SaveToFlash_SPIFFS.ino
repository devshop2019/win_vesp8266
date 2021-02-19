/*
   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Create a WiFi access point and provide a web server on it. */

#ifndef APSSID
#define APSSID "virus"
#define APPSK  "12345678"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

const char* PARAM_STRING = "inputString";
const char* PARAM_INT = "inputInt";
const char* PARAM_FLOAT = "inputFloat";

// HTML web page to handle 3 input fields (inputString, inputInt, inputFloat)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script>
    function submitMessage() {
      alert("Saved value to ESP SPIFFS");
      setTimeout(function(){ document.location.reload(false); }, 500);   
    }
  </script></head><body>
  <form action="/get" target="hidden-form">
    inputString (current value %inputString%): <input type="text" name="inputString">
    <input type="submit" value="Submit" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    inputInt (current value %inputInt%): <input type="number " name="inputInt">
    <input type="submit" value="Submit" onclick="submitMessage()">
  </form><br>
  <form action="/get" target="hidden-form">
    inputFloat (current value %inputFloat%): <input type="number " name="inputFloat">
    <input type="submit" value="Submit" onclick="submitMessage()">
  </form>
  <iframe style="display:none" name="hidden-form"></iframe>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
    Serial.println("- empty file or failed to open file");
    return String();
  }
  Serial.println("- read from file:");
  String fileContent;
  while(file.available()){
    fileContent+=String((char)file.read());
  }
  Serial.println(fileContent);
  return fileContent;
}

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
}

// Replaces placeholder with stored values
String processor(const String& var){
  //Serial.println(var);
  if(var == "inputString"){
    return readFile(SPIFFS, "/inputString.txt");
  }
  else if(var == "inputInt"){
    return readFile(SPIFFS, "/inputInt.txt");
  }
  else if(var == "inputFloat"){
    return readFile(SPIFFS, "/inputFloat.txt");
  }
  return String();
}

#define D13 14
void setup() {
  // Initialize SPIFFS
  #ifdef ESP32
    if(!SPIFFS.begin(true)){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
  #else
    if(!SPIFFS.begin()){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }
  #endif
  
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  pinMode(D13, OUTPUT);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/get?inputString=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET inputString value on <ESP_IP>/get?inputString=<inputMessage>
    if (request->hasParam(PARAM_STRING)) {
      inputMessage = request->getParam(PARAM_STRING)->value();
      writeFile(SPIFFS, "/inputString.txt", inputMessage.c_str());
    }
    // GET inputInt value on <ESP_IP>/get?inputInt=<inputMessage>
    else if (request->hasParam(PARAM_INT)) {
      inputMessage = request->getParam(PARAM_INT)->value();
      writeFile(SPIFFS, "/inputInt.txt", inputMessage.c_str());
    }
    // GET inputFloat value on <ESP_IP>/get?inputFloat=<inputMessage>
    else if (request->hasParam(PARAM_FLOAT)) {
      inputMessage = request->getParam(PARAM_FLOAT)->value();
      writeFile(SPIFFS, "/inputFloat.txt", inputMessage.c_str());
    }
    else {
      inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/text", inputMessage);
  });
  server.onNotFound(notFound);
  server.begin();
}

unsigned long timeee = 0, timeee2 = 0;
void loop() {
  if(millis() - timeee >= 3000){
    timeee = millis();
    digitalWrite(D13, digitalRead(D13)^1);
  }
  
  if(millis() - timeee2 >= 5000){
    // To access your stored values on inputString, inputInt, inputFloat
    String yourInputString = readFile(SPIFFS, "/inputString.txt");
    Serial.print("*** Your inputString: ");
    Serial.println(yourInputString);
    
    int yourInputInt = readFile(SPIFFS, "/inputInt.txt").toInt();
    Serial.print("*** Your inputInt: ");
    Serial.println(yourInputInt);
    
    float yourInputFloat = readFile(SPIFFS, "/inputFloat.txt").toFloat();
    Serial.print("*** Your inputFloat: ");
    Serial.println(yourInputFloat);
  }
}
