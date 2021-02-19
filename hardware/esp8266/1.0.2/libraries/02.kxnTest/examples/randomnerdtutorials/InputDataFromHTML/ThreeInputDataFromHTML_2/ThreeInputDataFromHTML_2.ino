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

   https://www.youtube.com/watch?v=9gq5lHMfHyI
    https://randomnerdtutorials.com/esp32-esp8266-input-data-html-form/
   
*/

/* Create a WiFi access point and provide a web server on it. */

//#include <ESP8266WiFi.h>
//#include <WiFiClient.h>
//#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "virus"
#define APPSK  "12345678"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

//ESP8266WebServer server(80);

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

const char* PARAM_INPUT_1 = "input1";
const char* PARAM_INPUT_2 = "input2";
const char* PARAM_INPUT_3 = "input3";

// HTML web page to handle 3 input fields (input1, input2, input3)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    input1: <input type="text" name="input1">
    <input type="submit" value="Submit">
  <br>
    input2: <input type="text" name="input2">
    <input type="submit" value="Submit">
  <br>
    input3: <input id="inputId3" type="text" name="input3">
    <input type="submit" value="Submit">
  </form>
  <button id="sendButton1" onclick="sendData()">Send Data</button>
  <script>
    function sendData(){
      var tempDataSend = "/data";//&inputId3=" + document.getElementById("inputId3").value;
//      var param = "&inputId3=" + document.getElementById("inputId3").value;
      var param = "&inputId3=222";

      var data = new FormData();
      data.append('inputId3', 'haha');
      
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function(){
        if(this.readyState == 4 && this.status == 200){
          document.getElementById("inputId3").value = this.responseText;
        }
      };
      console.log(tempDataSend);
      console.log(data);
      xhttp.open("PUT", '/data', true);
      xhttp.send("input3=222");
    }
  </script>
</body></html>)rawliteral";


void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
//void handleRoot() {
//  server.send(200, "text/html", "<h1>You are connected</h1>");
//}
#define D13 14
void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  pinMode(D13, OUTPUT);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
//  server.on("/", handleRoot);
//  server.begin();
//  Serial.println("HTTP server started");

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage, inputMessage2, inputMessage3;
    String inputParam, inputParam2, inputParam3;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
    }
    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
    else;
    if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      inputParam2 = PARAM_INPUT_2;
    }
    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
    else;
    if (request->hasParam(PARAM_INPUT_3)) {
      inputMessage3 = request->getParam(PARAM_INPUT_3)->value();
      inputParam3 = PARAM_INPUT_3;
    }
    else {
      inputMessage3 = "No message sent";
      inputParam3 = "none";
    }
    Serial.println(inputMessage);
    Serial.println(inputMessage2);
    Serial.println(inputMessage3);
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>");
  });

  server.on("/data", HTTP_PUT, [] (AsyncWebServerRequest *request) {
    Serial.println("Get \"/data\"");
    String inputMessage, inputMessage2, inputMessage3;
    String inputParam, inputParam2, inputParam3;
//    Serial.print("Example: ");
//    inputMessage3 = request->getParam(PARAM_INPUT_3)->value();
//    if(inputMessage3!= ""){
      Serial.println(String(request->params()));
//    }else Serial.println("Empty");
    
    if (request->hasParam(PARAM_INPUT_3)) {
      inputMessage3 = request->getParam(PARAM_INPUT_3)->value();
      inputParam3 = PARAM_INPUT_3;
      if(inputMessage3!= ""){
        Serial.println(inputMessage3);
      }
    }

//    request->send(200,"text/palain","inputMessage3");
    request->send(200,"text/palain",inputMessage3);
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
//  server.handleClient();
  digitalWrite(D13, digitalRead(D13)^1);
  delay(3000);
}
