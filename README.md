# ESP Self Sufficient OTA Library (ESP2SOTA)

<img src="https://www.pangodream.es/wp-content/uploads/2020/05/cropped-pangodream_2.0_hor_trans.png" align="right" alt="Pangodream Logo" width="120">

Based on the basic Arduino OTA example, this library gives you the possibility of updating Over The Air ESP8266 & ESP32 cards in both Wifi modes:
* Wifi Client mode
* **Wifi AP** mode

As you probably know, if you try to write in the **same sketch** the **WifiAccessPoint** code and the **OTAWebUpdater** one you will get an error in your web browser because OTAWebUpdater code tries to retrive jQuery library from the client browser, and that is something impossible because the ESP card is acting as Internet Gateway.
The solution is:
* Avoid using external Javascript libraries to control the binaries uploading to the ESP Webserver (this can be done by using Vanilla Javascript instead of jQuery)

Additionally, ESP2SOTA library improves significantly the aspect of OTAWebUpdater upload webpage:
<p align="center">
<img src="https://github.com/pangodream/ESP2SOTA/blob/main/docs/ESP2SOTA_Update_Screen.png?raw=true" alt="ESP2SOTA Upload page">
</p>

## Installation

* Download the latest version .zip file from **[GitHub]**
* Add the dowloaded library to your Arduino IDE

## Use
All you need (if your sketch already uses Webserver) to implement ESP2SOTA functionality in your sketch is:
* **Including:**
```
#include <ESP2SOTA.h>
```
and
* **Initializing:**
```
ESP2SOTA.begin(&server);
```

**If your sketch doesn't use Webserver** as part of it's functionality, both Client and AP examples show the needed code to support ESP2SOTA.

## Examples of use
You can find two different examples of implementation under the folder **examples**