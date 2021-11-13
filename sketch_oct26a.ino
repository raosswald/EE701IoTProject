
//Air Quality Setup -----------------------------------
#include "Adafruit_PM25AQI.h"
Adafruit_PM25AQI aqi = Adafruit_PM25AQI();

//GPS Setup -------------------------------------------

#include <Adafruit_GPS.h>
#define GPSSerial Serial4

Adafruit_GPS GPS(&GPSSerial);
#define GPSECHO false
uint32_t timer = millis();

//LoRa Setup ----------------------------------------

char mac_get_deveui[] = "mac get deveui \r\n";
uint8_t rx_buffer_data[50];

String incoming_byte;  

//*******************void setup PROGRAM START ******************************

void setup() {
  Serial1.begin(57600, SERIAL_8N1);
  Serial.begin(115200); 

  while(incoming_byte != "accepted\r\n") {
  Serial.print("sys reset\r\n");
  Serial1.print("sys reset\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }
     //delay(100);
     
  Serial.print("mac get deveui\r\n");
  Serial1.print("mac get deveui\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }

  Serial.print("mac set appeui 00250C0000010001\r\n");
  Serial1.print("mac set appeui 00250C0000010001\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }

  Serial.print("mac set appkey E343A7D5F8FA3F1241607C432D9D4457\r\n");
  Serial1.print("mac set appkey E343A7D5F8FA3F1241607C432D9D4457\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 

  Serial.print("mac set pwridx 10\r\n");
  Serial1.print("mac set pwridx 10\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 

  Serial.print("mac save\r\n");
  Serial1.print("mac save\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }

  Serial.print("sys reset\r\n");
  Serial1.print("sys reset\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 

  Serial.print("mac join otaa\r\n");
  Serial1.print("mac join otaa\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 

  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 
     //delay(1000);      
}
/*  Serial.print("mac tx cnf 4 5A5B5B\r\n");
  Serial1.print("mac tx cnf 4 01080100EF020012\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } */ 
 /* am2320.begin();
  Serial.print("mac tx cnf 4 5A5B5B\r\n");
  Serial1.print("mac tx cnf 4 010803ABCD04ABCD02ABCD\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }  */

     //GPS Setup ------------------------------------------------
     //Serial.begin(115200);
     Serial.println("Adafruit GPS library basic parsing test!");
     GPS.begin(9600);
     GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
     GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ); // 1 Hz update rate
     GPS.sendCommand(PGCMD_ANTENNA);
     delay(1000);
     GPSSerial.println(PMTK_Q_RELEASE);

     //Air Quality Setup ---------------------------------------
     //Serial is already set at 115200
      Serial.println("Adafruit PMSA003I Air Quality Sensor");
      Serial3.begin(9600);
     if (! aqi.begin_UART(&Serial3)) {
      Serial.println("Could not find PM 2.5 sensor!");
      while (1) delay(10);
     }
     Serial.println("PM25 found!");

     
}
bool ryanDebug = true;

//void loop PROGRAM CONTINUOUS START =================================================

void loop() {

  //delay(5000);

//AIR QUALITY STUFFS %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
/*
  PM25_AQI_Data data;
  if (! aqi.read(&data)) {
    //Serial.println("Could not read from AQI");
    //delay(500);  // try again in a bit!
    return;
  }
  //Serial.println("AQI reading success");
  Serial.print(F("Particles > 2.5um / 0.1L air:")); Serial.println(data.particles_25um);
  String AirQual = data.particles_25um;
  String compAir = AirQual + "F0B3";
  delay(1000);
  */
//GPS STUFFS ----------------------------------------------------------------
  char c = GPS.read();
  // if you want to debug, this is a good time to do it!
  if (GPSECHO)
    if (c) Serial.print(c);
  // if a sentence is received, we can check the checksum, parse it...
  if (GPS.newNMEAreceived()) {
    // a tricky thing here is if we print the NMEA sentence, or data
    // we end up not listening and catching other sentences!
    // so be very wary if using OUTPUT_ALLDATA and trying to print out data
    Serial.print(GPS.lastNMEA()); // this also sets the newNMEAreceived() flag to false
    if (!GPS.parse(GPS.lastNMEA())) // this also sets the newNMEAreceived() flag to false
      return; // we can fail to parse a sentence in which case we should just wait for another
  
  }
  
// approximately every 2 seconds or so, print out the current stats
  if (millis() - timer > 2000) {
    timer = millis(); // reset the timer

    Serial.print("Fix: "); Serial.println((int)GPS.fix);
    //Serial.print(" quality: "); Serial.println((int)GPS.fixquality);
    if (GPS.fix) {

    String la = GPS.latitude;
    //String lad = GPS.lat;
    String lo = GPS.longitude;
    //String lod = GPS.lon;
    String alt = GPS.altitude;
    

      Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      Serial.print(", ");
      Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      Serial.print("Altitude: "); Serial.println(GPS.altitude);

    la[4] = 'D';
    lo[4] = 'D';
    alt[3] = 'D';
    
    String complat = la + "F0B0";
    String complon = lo + "F0B1";
    String compalt = alt + "F0B2";
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    PM25_AQI_Data data;
  if (! aqi.read(&data)) {
    //Serial.println("Could not read from AQI");
    //delay(500);  // try again in a bit!
    return;
  }
  //Serial.println("AQI reading success");
  Serial.print(F("Particles > 2.5um / 0.1L air:")); Serial.println(data.particles_25um);
  String AirQual = data.particles_25um;
  String compAir = AirQual + "F0B3";
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//TRANSMISSION ---------------------------------------------------------------
//LATTITUDE TRANSMISSION===================================================
  Serial.print("mac tx cnf 4 Lat Transmission\r\n");
  Serial1.print("mac tx cnf 4 " + complat + "\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }
     
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 
  while(incoming_byte == "mac_err\r\n") {
  Serial.print("mac tx cnf 4 Lat Transmission\r\n");
  Serial1.print("mac tx cnf 4 " + complat + "\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }
     
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 
  }
// LONGITUDE TRANSMISSION ======================================

  Serial.print("mac tx cnf 4 Long Transmission\r\n");
  Serial1.print("mac tx cnf 5 " + complon + "\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }
  
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }
  while(incoming_byte == "mac_err\r\n") {
  Serial.print("mac tx cnf 4 Long Transmission\r\n");
  Serial1.print("mac tx cnf 5 " + complon + "\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }
  
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 
  }
//ALTITUDE TRANSMISSION ==================================
  Serial.print("mac tx cnf 4 Alt Transmission\r\n");
  Serial1.print("mac tx cnf 6 " + compalt + "\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }

  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 
  while(incoming_byte == "mac_err\r\n") {
  Serial.print("mac tx cnf 4 Alt Transmission\r\n");
  Serial1.print("mac tx cnf 6 " + compalt + "\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }

  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 
  }
//Air Quality Transmission %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%55

  Serial.print("mac tx cnf 4 Air Quality Transmission\r\n");
  Serial1.print("mac tx cnf 7 " + compAir + "\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }

  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 
  while(incoming_byte == "mac_err\r\n") {
  Serial.print("mac tx cnf 4 Air Quality Transmission\r\n");
  Serial1.print("mac tx cnf 7 " + compAir + "\r\n");
  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     }

  while(Serial1.available()==0) {}
  if (Serial1.available()) {
     incoming_byte = Serial1.readString();
     Serial.print(incoming_byte);
     } 
  }

//================================================
//------------End Transmisssions------------------
//================================================    
    }
  }
     
}
