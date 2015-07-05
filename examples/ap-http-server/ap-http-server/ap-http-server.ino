#include "Arduino.h"
#include "SoftwareSerial.h"
#include <ESP8266_Simple.h>

#define ST_SSID "wireless"
#define ST_SSID "smilingstreet384"

#define AP_SSID "esp1234"
#define AP_PASS "1234test"

ESP8266_Simple wifi(2,3);

void setup() {
  Serial.begin(9600);
  Serial.println("ESP8266 Hybrid Sketch");

  wifi.begin(9600);

  wifi.setWifiMode(ESP8266_BOTH);

  wifi.setupAsWifiNetwork(AP_SSID, AP_PASS, 5, ESP8266_ECN_WPA2_PSK);

  static ESP8266_HttpServerHandler httpServerHandlers[] = {
    { PSTR("GET /discover"),  httpDiscover },
    { PSTR("GET "),           http404    } 
  };

  wifi.startHttpServer(80, httpServerHandlers, sizeof(httpServerHandlers), 250, &Serial);

  Serial.println();  
}

void loop() {
   wifi.serveHttpRequest();
}

unsigned long httpDiscover(char *buffer, int bufferLength) {
  memset(buffer, 0, bufferLength);  
  strcpy_P(buffer, PSTR("<h1>DONE BIG PUN</h1>"));
  
  return ESP8266_HTML | 200;
}

unsigned long http404(char *buffer, int bufferLength) {
  memset(buffer, 0, bufferLength);  
  strcpy_P(buffer, PSTR("<h1>Error, Unknown Command</h1>\r\n<p>Try <a href=\"/millis\">/millis</a>, and <a href=\"/led\">/led</a></p>"));
  
  return ESP8266_HTML | 404;
}
