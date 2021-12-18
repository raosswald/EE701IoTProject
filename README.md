# MapMyAir
MapMyAir is a proof of concept system to viusalize and predict air quality in your local neighboorhood. MapMyAir uses the LoraWan(proprietary low-power wide-area network) to collect air quality metrics with custom hardware. The collected data is formated and sent to ThingSpeak, then pulled from the ThingSpeak Channel to a custom client GUI application. This system was deployed at the University at Buffalo's North Campus. 

> ![Map My Air Client Application](/Documentation/MapMyAirClientApp.png)
> 
> MapMyAir Client Application GUI

[![IMAGE ALT TEXT HERE](https://img.youtube.com/vi/I_mFrcK4Gwo/0.jpg)](https://www.youtube.com/watch?v=I_mFrcK4Gwo)
---
## Hardware

The custom hardware runs on a Teensy 3.6 programmed with the Arduino IDE.  Communication to the GPS, LoRa Radio, and Air Quality sensor is done with Serial.  Teensy provides extra serial ports to communicate with the modules along with a serial connection to PC which is why this microcontroller was chosen. Other than the LoRa Radio, all components are off the shelf and links are provided below.
> ![MapMyAir Hardware](/Documentation/HardwareMapMyAir.png)
> 
> MapMyAir Custom Hardware


| Component & Link | Description | Price(USD) |
| ---------- | ---- |  -----|
| [Teensy 3.6](https://www.pjrc.com/store/teensy36.html) | Microcontroller | $29.25 |
| [PM2.5 Air Quality Sensor and Breadboard Adapter Kit - PMS5003](https://www.adafruit.com/product/3686?gclid=CjwKCAjwyvaJBhBpEiwA8d38vKnVx_Y_iaRcCHO7B19t33FtbRdYeCRXTI9LNg5BnFYp2_uByk9vkhoCoagQAvD_BwE) | PM2.5 Air Quality Sensor | $39.95 | 
| [Adafruit Ultimate GPS Breakout - 66 channel w/10 Hz updates - Version 3](https://www.adafruit.com/product/746?gclid=CjwKCAiAh_GNBhAHEiwAjOh3ZBlegc6uSpFTh-ZUeaweLcAKE87Fj8o2H1fkPLiSAkeLeGEUTl2ysRoCUHEQAvD_BwE)| GPS Module | $29.95 |
| RN2903 Custom Lora Module PCB | Lora Radio Module | |
|Total | | $99.85 |
___

## Dependencies

All the libraries used in MapMyAir are free and available for download.

```py
from urllib.request import urlopen
import sys, folium, json, math
import numpy as np
from PyQt5.QtCore import hex_
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QGridLayout, QLabel, QLineEdit, QFormLayout
from PyQt5.QtWebEngineWidgets import QWebEngineView
```
>Python Libraries

```cpp
#include "Adafruit_PM25AQI.h"
#include <Adafruit_GPS.h>
```
>Arduino Libraries
___

## Custom Packet Structure

___

## Cloud Database