import requests
#import random
#import math
import urllib. request
import numpy as np
import joblib
#import threading
import time
import json

# Path to the trained joblib ML model
model_path =r"Add your model pathname"  

# Load the ML model
model = joblib.load(model_path)



def fetch_precipitation_data(api_key, city_name):
    base_url = "https://api.openweathermap.org/data/2.5/weather"
    params = {
        "q": city_name,
        "appid": api_key,
        "units": "metric"
    }

    response = requests.get(base_url, params=params)

    if response.status_code == 200:
        data = response.json()
        precipitation = data.get("rain", 0)

        return precipitation
    else:
        print("Error: Unable to fetch precipitation data.")
        return None



def thingspeak_publish(val1):
    #threading.Timer(15,thingspeak).start()
    URL='https://api.thingspeak.com/update?api_key='
    KEY='Z7BY88XQIZNIPFB0'
    HEADER='&field4={val:.2f}'.format(val=val1)
    new_URL=URL+KEY+HEADER
    #v=urllib.request(new_URL)
    data=urllib.request.urlopen(new_URL)
    print(data)
    print("succesfully published")


def isnan(num):
    return num!=num

result=[0.00,0.00]
def thinkspeak_subscribe():
    # ThingSpeak API endpoint and parameters
    api_endpoint = "https://api.thingspeak.com/channels/2094506/feeds.json"
    api_key = "A59BQKALSU14W6X8"  # Replace with your ThingSpeak read API key
    results = 1   # Number of latest results to retrieve

    # Construct the API request URL
    api_url = "{}?api_key={}&results={}".format(api_endpoint, api_key, results)

    # Send GET request to the API
    response = requests.get(api_url)

    # Parse the response JSON
    data = json.loads(response.text)

    # Check if the API request was successful
    if response.status_code == 200:
        # Extract the latest temperature and humidity values
        entries = data["feeds"]
        print(entries)
        if len(entries) > 0:
            try:
                if entries[0].get("field1")!=None and entries[0].get("field2")!=None:
                    result[0] = entries[0].get("field1")
                    result[1] = entries[0].get("field2")
            except:
                pass
        else:
            print("No data available.")
    else:
        print("Failed to fetch data. Error code:", response.status_code)


# Provide your OpenWeatherMap API key and the city name for the desired location
api_key = "d4c7d955b03c5afb379b60c7a17860e1"
city_name = "Kolkata,IN"




while True:
    precipitation=fetch_precipitation_data("d4c7d955b03c5afb379b60c7a17860e1", "Kolkata,IN")

    # Print the precipitation data
    if precipitation is not None:
        print(f"Precipitation: {precipitation} mm")
    
    thinkspeak_subscribe()
#    if result[0] is None:
 #       result[0]=33.56
  #  if result[1] is None:
#        result[1]=52.00    
    print("temperature: {0} , humidity:{1}",result[0],result[1])
    # Preprocess the data
    data = np.array([[result[0], result[1],1,precipitation]] )
    # Apply the ML model for prediction
    prediction = model.predict(data)
    prediction=float(prediction)
    print(f"Prediction: {prediction} %")
    thingspeak_publish(prediction)
    time.sleep(10)
