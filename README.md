# MapMyAir
MapMyAir is a proof of concept system to visualize and predict air quality in your local neighborhood. MapMyAir uses the LoRaWAN(proprietary low-power wide-area network) to collect air quality metrics with custom hardware. The custom hardware is moved around your local area and collects data about the air. The collected data is formatted and forwarded to ThingSpeak after being transmitted over LoRaWAN, then pulled from a ThingSpeak Channel to a custom client GUI application. This system was deployed at the University at Buffalo's North Campus. 

> ![Map My Air Client Application](/Documentation/MapMyAirClientApp.png)
> 
> MapMyAir Client Application GUI running on MacOS

### Video Demonstration
https://www.youtube.com/watch?v=I_mFrcK4Gwo

## Hardware

The custom hardware runs on a Teensy 3.6 programmed with the Arduino IDE.  Communication to the GPS, LoRa Radio, and Air Quality sensor is done with Serial.  Teensy provides extra serial ports to communicate with the modules along with a serial connection to PC which is why this micro-controller was chosen. Other than the LoRa Radio, all components are off the shelf and links are provided below.
> ![MapMyAir Hardware](/Documentation/HardwareMapMyAir.png)
> 
> MapMyAir Custom Hardware


| Component & Link | Description | Price(USD) |
| ---------- | ---- |  -----|
| [Teensy 3.6](https://www.pjrc.com/store/teensy36.html) | Micro-controller | $29.25 |
| [PM2.5 Air Quality Sensor and Breadboard Adapter Kit - PMS5003](https://www.adafruit.com/product/3686?gclid=CjwKCAjwyvaJBhBpEiwA8d38vKnVx_Y_iaRcCHO7B19t33FtbRdYeCRXTI9LNg5BnFYp2_uByk9vkhoCoagQAvD_BwE) | PM2.5 Air Quality Sensor | $39.95 | 
| [Adafruit Ultimate GPS Breakout - 66 channel w/10 Hz updates - Version 3](https://www.adafruit.com/product/746?gclid=CjwKCAiAh_GNBhAHEiwAjOh3ZBlegc6uSpFTh-ZUeaweLcAKE87Fj8o2H1fkPLiSAkeLeGEUTl2ysRoCUHEQAvD_BwE)| GPS Module | $29.95 |
| RN2903 Custom Lora Module PCB | Lora Radio Module | |
|Total | | $99.85 |

## Client Application

### Overview

MapMyAir's Client Application runs on Python using PyQt5 and Leaflet. Leaflet generates a map using HTML that is displayed in the custom application built with PyQt5.  Leaflet is an open-source JavaScript library for mobile-friendly interactive maps that has been ported to Python. This library provides an easy way to utilize and display Geo-Spatial data.

### Markers

Collected data is pulled from the database on ThingSpeak and used to create markers to display the collected data when clicked.  Each marker has six attributes:

1. Latitude
2. Longitude
3. Altitude
4. PM2.5
5. Date/Time
6. Classification

The first five attributes are collected by the custom hardware and sent to a ThingSpeak Channel with a custom packet structure. The classification is determined by the client application based on the PM2.5 reading.

Markers are separated into three classes:

| PM2.5 Range | Classification | Description |
| --- | --- | ---|
| 0 - 5 | Green| "Air is clean, no precautions for going outside" | 
| 5 - 10 | Orange | "Air has some pollution, take precaution when outside" |
| > 10| Red | "Air is very polluted, mask wearing recommended" |

> ![Map My Air Client Application](/Documentation/MapMyAirMap1.png)
> 
> MapMyAir Markers Example

### Air Quality Prediction

The markers plotted are used for a qualitative prediction of the air quality by specifying GPS-coordinates. The K-Nearest Neighbors algorithm is used to classify the user given coordinates.  The algorithm looks at the class of the closest four markers using the Euclidean Distance of the user given coordinate to all of the markers.  The user given coordinate is then classified and a recommendation is displayed on the GUI. This function is run when the user clicks the "Predict!" button on the GUI.

> ![Map My Air Client Application](/Documentation/MapMyAirPrediction.png)
> 
> MapMyAir Prediction Example




## Custom Packet Structure

Since the packets sent over LoRaWAN are meant to be small in size and limited to Hexa-Decimal digits a custom packet structure was developed for the sent payloads. The micro-controller encodes the data to the hexadecimal packet structure before transmitting the packet over LoRaWAN. The client application then decodes the packets to useable data when a new marker is generated.

### HexaDecimal Key

| Hex Code | Meaning |
| --- | --- |
| 0xD | Decimal Point '.' |
| 0xF | Frame Identifier placed before Frame Number |
| 0xB | Type Identifier placed before Type ID|

### Type IDs

| Type | HEX ID  |
| --- | --- |
| Latitude |0x0 |
| Longitude | 0x1 |
| Altitude | 0x2 |
| PM2.5 AQI | 0x3 |

### Packet Format
| [Data] | 0xF | [Frame Number] | 0xB | [Data Type] |
|--- | --- | --- | ---| --- |

### Example 

>An example of a payload packet will look like:
>
>0x0190D20F13B2
>
>The packet represent:
>| Data | Frame | Data Type|
>| --- | --- | --- |
>| 190.20 | 13 | Altitude | 



## Cloud Database
[ThingSpeak](https://thingspeak.com/) is used as the cloud database to store the received packets from LoRaWAN.  The packets are all sent to one channel on ThingSpeak in our custom Packet Structure. The channel is accessible anywhere there is an internet connection. The client application accesses our data using a URL to simply read the data in the channel. The data gets stored in the JSON format and is converted to a Python Dictionary to easily access the data. The data packet is stored in 'field1' and the time that the data was received at is stored in 'created_at'.

> ![Map My Air Client Application](/Documentation/MapMyAirJSON.png)
> 
> MapMyAir JSON Example
> 
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


## Credits
Ryan Osswald | Software Implementation

Erik Vickerd | Hardware Implementation

University at Buffalo Department of Electrical Engineering | Hardware Funding
