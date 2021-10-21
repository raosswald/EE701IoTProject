import json
from urllib.request import urlopen

def getJson(url):
    response = urlopen(url)
    data = response.read().decode("utf-8")
    return json.loads(data)

jsonDic = getJson("https://api.thingspeak.com/channels/1541460/feeds.json?results=2")

#how to access data, this function creates a dictionaty
#print(jsonDic['channel']['last_entry_id'])