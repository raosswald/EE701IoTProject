import urllib.request
import time

gpsLat = [43.0, 43.0]
gpslong = [-79, -79]
temp = [68, 68]


for i in range(2):
    b = urllib.request.urlopen("https://api.thingspeak.com/update?api_key=4CVTL9AUPIO3FUHO&field1=" + str(gpsLat[i]) + "&field2=" + str(gpslong[i]) + "&field4=" + str(temp[i]))
    
    time.sleep(2)
    b.close()
    
