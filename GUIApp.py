from urllib.request import urlopen
import sys, folium, json
import numpy as np
from PyQt5.QtCore import hex_
from PyQt5.QtWidgets import QMainWindow, QApplication, QVBoxLayout, QWidget, QPushButton
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

    dataTypes = 4
    frames = 0

    #find the number of different frames
    frameIds = []
    for i in range(markerCount):
        hexData = jsonDic['feeds'][i]['field1']
        frameNum = int(hexData[hexData.find('F') + 1])
        if(frameNum not in frameIds):
            frameIds.append(frameNum)
            #Use this number to create an array
            frames += 1

    #creates a correct sized array with unique v
    organizedData = np.full(shape=(frames, dataTypes), fill_value=None)    
    hexDataBank = []

    #Get rid of repeat data
    for j in range(markerCount):
        hexData = jsonDic['feeds'][j]['field1']
        if hexData not in hexDataBank:
            hexDataBank.append(hexData)
        #DO ME NEXT!!!!!!!  
        #append data correctly in organizedData Array


    #append data to organizedData
    for currentHex in hexDataBank:

        
        #Get data out of hex string to a useable format
        dataType = int(currentHex[currentHex.find('B') + 1])
        frameNum = int(currentHex[currentHex.find('F') + 1])
        infoData = currentHex[0 : currentHex.find('F')]
        if('D' in infoData):
            infoData = float(infoData.replace('D', '.'))
        else:
            infoData = float(infoData)


        #this organizes the payload into a useable array
        iterInOrganizedData = frameIds.index(frameNum)

        if(organizedData[iterInOrganizedData][dataType] == None):
            organizedData[iterInOrganizedData][dataType] = infoData
        


    
    #print(hexDataBank)
    

    print(organizedData)
    for i in range(organizedData.size[0]):
        
    #folium.Marker(location=[43, -78.7849], popup="Center of the Map", tooltip="Click for Data", icon=folium.Icon(color='orange')).add_to(map)






#https://zetcode.com/pyqt/qwebengineview/
class Example(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        vbox = QVBoxLayout(self)

        self.webEngineView = QWebEngineView()
        self.loadPage()

        # NewMap = QPushButton("Update Map")
        # NewMap.clicked.connect(self.GenerateNewMap)

        button = QPushButton("Reload Map")
        button.clicked.connect(self.loadPage)

        vbox.addWidget(self.webEngineView)
        vbox.addWidget(button)
        # vbox.addWidget(NewMap)

        self.setLayout(vbox)

        self.setGeometry(300, 300, 750, 650)
        self.setWindowTitle('MapMyAir')
        self.show()

    def loadPage(self):
        #To Do:
        #pull sample markers from thingspeak and populate map

        #Generates new Base Map
        map = folium.Map(location=[43, -79])

        #download data from cloud as JSON dic
        jsonData = getJson("https://thingspeak.com/channels/1541460/field/1.json")
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