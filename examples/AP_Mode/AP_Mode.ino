#include <WiFi.h>
#include <WiFiAP.h>
#include <WebServer.h>
/* INCLUDE ESP2SOTA LIBRARY */
#include <ESP2SOTA.h>

const char* ssid = "ESP2SOTA";
const char* password = "123456789abc";

WebServer server(80);

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);  
  WiFi.softAP(ssid, password);
  delay(1000);
  IPAddress IP = IPAddress (10, 10, 10, 1);
  IPAddress NMask = IPAddress (255, 255, 255, 0);
  WiFi.softAPConfig(IP, IP, NMask);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  /* SETUP YOR WEB OWN ENTRY POINTS */
  server.on("/myurl", HTTP_GET, []() {
    server.sendHeader("Connection", "close");
    server.send(200, "text/plain", "Hello there!");
  });

  /* INITIALIZE ESP2SOTA LIBRARY */
  ESP2SOTA.begin(&server);
  server.begin();
}

void loop(void) {
  /* HANDLE UPDATE REQUESTS */
  server.handleClient();

  /* YOUR LOOP CODE HERE */


  
  delay(5);
}