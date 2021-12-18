# MapMyAir
MapMyAir is a proof of concept system to viusalize and predict air quality in your local neighboorhood. MapMyAir uses the LoRaWAN(proprietary low-power wide-area network) to collect air quality metrics with custom hardware. The custom hardware is moved around your local area and collects data about the air. The collected data is formated and sent to ThingSpeak over LoRaWAN, then pulled from the ThingSpeak Channel to a custom client GUI application. This system was deployed at the University at Buffalo's North Campus. 

> ![Map My Air Client Application](/Documentation/MapMyAirClientApp.png)
> 
> MapMyAir Client Application GUI running on MacOS

### Vide Demonstration
https://www.youtube.com/watch?v=I_mFrcK4Gwo

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

## Client Application

### Overview

MapMyAir's Client Application runs on Python using PyQt5 and Leaflet. Leaflet generates a map using HTMML that is displayed in the custom application built with PyQt5.  Leaflet is an open-source JavaScript library for mobile-friendly interactive maps that has been ported to Python. This library provides an easy way to utilize and display Geo-Spatial data.

### Markers

Collected data is pulled from the database on ThingSpeak and used to create markers to display the collected data when clicked.  Each marker has six attributes:

1. Latitude
2. Longitude
3. Altitude
4. PM2.5
5. Date/Time
6. Classification

The first five attributes are collected by the custom hardware and sent to a ThingSpeak Channel with a custom packet structure. The classification is determined by the client application based on the PM2.5 reading.

Markers are seperated into three classes:

| PM2.5 Range | Classification | Description |
| --- | --- | ---|
| 0 - 5 | Green| "Air is clean, no precautions for going outside" | 
| 5 - 10 | Orange | "Air has some pollution, take precaution when outside" |
| > 10| Red | "Air is very polluted, mask wearing reccomended" |

> ![Map My Air Client Application](/Documentation/MapMyAirMap1.png)
> 
> MapMyAir Markers Example

### Air Quality Prediction

The markers plotted are used for a qualitative prediction of the air quality by specifying GPS-coordinates. The K-Nearest Neighbors algorithm is used to classify the user given coordinates.  The algorithm looks at the class of the closest four markers using the Euclidian Disatance of the user given coordinate to all of the markers.  The user given coordinate is then classified and a reccomendation is displayed on the GUI. This function is run when the user clicks the "Predict!" button on the GUI.

> ![Map My Air Client Application](/Documentation/MapMyAirPrediction.png)
> 
> MapMyAir Prediction Example




## Custom Packet Structure


## Cloud Database
 
## Dependencies

All the libraries used in MapMyAir are free and available for download.

>```py
>from urllib.request import urlopen
>import sys, folium, json, math
>import numpy as np
>from PyQt5.QtCore import hex_
>from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QGridLayout, QLabel, QLineEdit, QFormLayout
>from PyQt5.QtWebEngineWidgets import QWebEngineView
>```
>Python Libraries

>```cpp
>#include "Adafruit_PM25AQI.h"
>#include <Adafruit_GPS.h>
>```
>Arduino Libraries

## Reflections & Further Work

## Credits
Erik Vickerd | Hardware Implementation

University at Buffalo Department of Electrical Engineering | Hardware Funding
