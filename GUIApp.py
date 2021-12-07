from urllib.request import urlopen
import sys, folium, json
import numpy as np
from PyQt5.QtCore import hex_
from PyQt5.QtWidgets import QMainWindow, QApplication, QWidget, QPushButton, QGridLayout, QLabel, QLineEdit, QFormLayout
from PyQt5.QtWebEngineWidgets import QWebEngineView




def getJson(url):
    # this function pulls the json data from an url and creates a dictionary
    #access the dictionary in the following way
    #print(jsonDic['channel']['last_entry_id'])
    response = urlopen(url)
    data = response.read().decode("utf-8")
    return json.loads(data)



def createMarkersfromJSON(jsonDic, map):

    markerCount = len(jsonDic['feeds'])

    dataTypes = 5
    frames = 0

    
    #clean air range = 0-5
    cleanBound = 5
    #caution range = 5-10
    dangerBound = 10
    #danger range > 10
    markerColor = 'white'

    #find the number of different frames
    frameIds = []
    for i in range(markerCount):
        hexData = jsonDic['feeds'][i]['field1']
        #needs to read frames past nine
        frameNum = int(hexData[hexData.find('F') + 1: hexData.find('B')])
        if(frameNum not in frameIds):
            frameIds.append(frameNum)
            #Use this number to create an array
            frames += 1

    #creates a correct sized array with unique v
    organizedData = np.full(shape=(frames, dataTypes), fill_value=None)    
    hexDataBank = []
    timeDataBank = []

    #Get rid of repeat data
    for j in range(markerCount):
        hexData = jsonDic['feeds'][j]['field1']
        timeData = jsonDic['feeds'][j]['created_at']
        if hexData not in hexDataBank:
            hexDataBank.append(hexData)
            timeDataBank.append(timeData)
        #DO ME NEXT!!!!!!!  
        #append data correctly in organizedData Array

    #print(frameIds)
    #print(hexDataBank)
    timeIteration = 0;
    #append data to organizedData
    for currentHex in hexDataBank:


        #Get data out of hex string to a useable format
        dataType = int(currentHex[currentHex.find('B') + 1])
        frameNum = int(currentHex[currentHex.find('F') + 1 : currentHex.find('B')])
        infoData = currentHex[0 : currentHex.find('F')]
        if('D' in infoData):
            infoData = infoData.replace('D', '.')
        # else:
        #     infoData = float(infoData)


        #this organizes the payload into a useable array
        iterInOrganizedData = frameIds.index(frameNum)

        if(organizedData[iterInOrganizedData][dataType] == None):
            organizedData[iterInOrganizedData][dataType] = infoData

        #append time to organized arrry, will have to change spot
        if(organizedData[iterInOrganizedData][4] == None):
            organizedData[iterInOrganizedData][4] = timeDataBank[timeIteration]
        
        timeIteration += 1

        


    
    #print(hexDataBank)
    

    #print(organizedData)
    for i in range(organizedData.shape[0]):
        #convert lat and long to decimal
        if(organizedData[i][0] != None and organizedData[i][1] != None):
            if(organizedData[i][0][0] =='0'):
                latitude = float(organizedData[i][0][0:3]) +  float(organizedData[i][0][3:])/60  
                #print(latitude)
                longitude = float(organizedData[i][1][0:3]) +  float(organizedData[i][1][3:])/60 
                #print(longitude)
            else:
                latitude = float(organizedData[i][0][0:2]) +  float(organizedData[i][0][2:])/60
                longitude = float(organizedData[i][1][0:2]) +  float(organizedData[i][1][2:])/60 

            #classifies markers based on air quality
            if(organizedData[i][3] != None):
                currentPM = int(organizedData[i][3])
                print(currentPM)
                if(currentPM <= cleanBound):
                    markerColor = 'green'
                elif(currentPM > cleanBound and currentPM < dangerBound):
                    markerColor = 'orange'
                elif(currentPM >= dangerBound):
                    markerColor = 'red'


                folium.Marker(location=[latitude, -longitude], 
                            popup=folium.Popup(html="<br><b>latitude: </b>" + str(latitude) + "</br>"
                            + "<br><b>longitude: </b>" + str(longitude) + "</br>"
                            + "<br><b>altitude: </b>" + organizedData[i][2] + "</br>"
                            + "<br><b>PM2.5: </b>" + organizedData[i][3] + "</br>"
                            + "<br><b>Date: </b>\n<i>" + organizedData[i][4] + "</i></br>"), 
                            icon=folium.Icon(color=markerColor)
                            ).add_to(map)






#https://zetcode.com/pyqt/qwebengineview/
class Example(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        #vbox = QVBoxLayout(self)
        gridLayout = QGridLayout()

        self.webEngineView = QWebEngineView()
        self.loadPage()

        # NewMap = QPushButton("Update Map")
        # NewMap.clicked.connect(self.GenerateNewMap)
        
        button = QPushButton("Reload Map")
        button.clicked.connect(self.loadPage)

        textLabel = QLabel("Air Quality Prediction:")


        latBox = QLineEdit()
        longBox = QLineEdit()

        gridLayout.addWidget(self.webEngineView, 0, 0)
        gridLayout.addWidget(button, 1, 0)
        gridLayout.addWidget(textLabel, 2, 0)
        gridLayout.addWidget(latBox, 3, 0)
        gridLayout.addWidget(longBox, 4, 0)
        
        # vbox.addWidget(NewMap)

        self.setLayout(gridLayout)

        self.setGeometry(300, 300, 750, 650)
        self.setWindowTitle('MapMyAir')
        self.show()

    def loadPage(self):
        #To Do:
        #pull sample markers from thingspeak and populate map

        #Generates new Base Map
        map = folium.Map(location=[43.002, -78.785], zoom_start=16)

        #download data from cloud as JSON dic
        jsonData = getJson("https://api.thingspeak.com/channels/1541460/fields/1.json?results=1000")
        createMarkersfromJSON(jsonData, map)
        
        #saves the map as html
        map.save("index.html")

        #opens map
        with open('index.html', 'r') as f:

            html = f.read()
            self.webEngineView.setHtml(html)

    # def GenerateNewMap(self):
        
    #     map = folium.Map(location=[43, -78.7849])
    #     folium.Marker(location=[43, -78.7849], popup="Center of the Map", tooltip="Click for Data", icon=folium.Icon(color='orange')).add_to(map)
    #     map.save("index.html")





if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = Example()
    window.show()
    sys.exit(app.exec_())