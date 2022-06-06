#include <WiFi.h>
/*#include <WiFiClient.h>*/
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESP2SOTA.h>

const char* ssid = "ESP32-OTA";
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

  ESP2SOTA.begin(&server);
  
  server.begin();
}

void loop(void) {
  server.handleClient();
  delay(1);
}
