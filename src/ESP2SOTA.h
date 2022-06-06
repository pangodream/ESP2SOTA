#ifndef ESP2SOTA_h
    #define ESP2SOTA_h
    #include "Arduino.h"
    #include "stdlib_noniso.h"
    #if defined(ESP8266)
        #define HARDWARE "ESP8266"
        #include "ESP8266WebServer.h"
        #include "ESP8266HTTPUpdateServer.h"
    #elif defined(ESP32)
        #define HARDWARE "ESP32"
        #include "WebServer.h"
        #include "Update.h"
    #endif
    
    class ESP2SOTAClass{
      public:
        ESP2SOTAClass();
        #if defined(ESP8266)      
          void begin(ESP8266WebServer *server);
        #elif defined(ESP32)
          void begin(WebServer *server);
        #endif
      private:
        #if defined(ESP8266)
            ESP8266WebServer *_server;
            ESP8266HTTPUpdateServer _httpUpdater;
        #endif
        #if defined(ESP32)
            WebServer *_server;
        #endif     
    };
    extern ESP2SOTAClass ESP2SOTA;
#endif
