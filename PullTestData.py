import json
from urllib.request import urlopen

def getJson(url):
    response = urlopen(url)
    data = response.read().decode("utf-8")
    return json.loads(data)

jsonDic = getJson("https://thingspeak.com/channels/1541460/feed.json")

print(jsonDic)

#how to access data, this function creates a dictionaty
#print(jsonDic['channel']['last_entry_id'])