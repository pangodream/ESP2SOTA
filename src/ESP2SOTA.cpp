#include "ESP2SOTA.h"
#include "index_html.h"
//Class constructor
ESP2SOTAClass::ESP2SOTAClass(){

}

#if defined(ESP8266)
  void ESP2SOTAClass::begin(ESP8266WebServer *server){
#elif defined(ESP32)
  void ESP2SOTAClass::begin(WebServer *server){
#endif
  _server = server;
  //Returns index.html page
  _server->on("/update", HTTP_GET, [&]() {
    _server->sendHeader("Connection", "close");
    _server->send(200, "text/html", indexHtml);
  });

  /*handling uploading firmware file */
  _server->on("/update", HTTP_POST, [&]() {
    _server->sendHeader("Connection", "close");
    _server->send(200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
    ESP.restart();
  }, [&]() {
    HTTPUpload& upload = _server->upload();
    if (upload.status == UPLOAD_FILE_START) {
      Serial.printf("Update: %s\n", upload.filename.c_str());
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) { //start with max available size
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      /* flashing firmware to ESP*/
      if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
        Update.printError(Serial);
      }
    } else if (upload.status == UPLOAD_FILE_END) {
      if (Update.end(true)) { //true to set the size to the current progress
        Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
      } else {
        Update.printError(Serial);
      }
    }
  });
}

ESP2SOTAClass ESP2SOTA;
