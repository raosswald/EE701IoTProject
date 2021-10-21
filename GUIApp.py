import os
import urllib
import sys
import folium
from folium import features
from PyQt5.QtWidgets import QMainWindow, QApplication, QVBoxLayout, QWidget, QPushButton
from PyQt5.QtWebEngineWidgets import QWebEngineView

#https://zetcode.com/pyqt/qwebengineview/
class Example(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        vbox = QVBoxLayout(self)

        self.webEngineView = QWebEngineView()
        self.loadPage()

        NewMap = QPushButton("Update Map")
        NewMap.clicked.connect(self.GenerateNewMap)

        button = QPushButton("Reload Map")
        button.clicked.connect(self.loadPage)

        vbox.addWidget(self.webEngineView)
        vbox.addWidget(button)
        vbox.addWidget(NewMap)

        self.setLayout(vbox)

        self.setGeometry(300, 300, 550, 450)
        self.setWindowTitle('MapMyAir')
        self.show()

    def loadPage(self):

        with open('index.html', 'r') as f:

            html = f.read()
            self.webEngineView.setHtml(html)

    def GenerateNewMap(self):
        
        map = folium.Map(location=[43, -78.7849])
        map.save("index.html")





if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = Example()
    window.show()
    sys.exit(app.exec_())