# Smart-Irrigation-system-using-ML-and-IoT
Smart irrigation systems that use IoT sensors and machine learning algorithms can help monitor soil moisture for better water management and crop productivity.  Cloud computing can also be utilized for remote data storage and processing, which eliminates the need for manual soil checking and minimizes crop damage from water supply failure.


![image](https://github.com/Avdhesh616/Smart-Irrigation-system-using-ML-and-IoT/assets/75134990/0e7e4ea9-3a37-4b98-9b39-5325eaec139a)

![image](https://github.com/Avdhesh616/Smart-Irrigation-system-using-ML-and-IoT/assets/75134990/a3709bcd-03fd-4f10-be5e-e949e379dd07)

![image](https://github.com/Avdhesh616/Smart-Irrigation-system-using-ML-and-IoT/assets/75134990/aea83f98-93d4-4a17-8279-ebce6bc34ca8)



![image](https://github.com/Avdhesh616/Smart-Irrigation-system-using-ML-and-IoT/assets/75134990/6e9e0d1a-5fed-4fec-bd0f-1bb867160369)

![image](https://github.com/Avdhesh616/Smart-Irrigation-system-using-ML-and-IoT/assets/75134990/73f0869e-f056-4014-a920-66477c0202b7)

Here The Motor in the circuit diagram has been denoted as LED bulb.


# Working
The Node MCU board is a compact electronic device with internet connectivity and programmability. It incorporates a DHT11 sensor to measure temperature and humidity.

The Node MCU board acquires temperature and humidity readings from the DHT11 sensor. The code for the Node MCU board is provided in the file "irrigation_system.ino".

These readings are then transmitted to the ThingSpeak IoT cloud platform. ThingSpeak is a cloud-based service designed for data collection, analysis, and visualization from IoT devices.

On the central controller, a Python program, the temperature, and humidity values are retrieved from the ThingSpeak cloud. This program interacts with other components to make informed decisions. You just need to run this python program in the terminal(It requires internet).

The central controller fetches the precipitation value from an API. An API (Application Programming Interface) is a set of rules and protocols enabling software applications to communicate with each other. In this context, the API provides information on precipitation levels.

The central controller prompts the user to manually input the crop type. This input is crucial for determining the specific crop's required soil moisture level.

Utilizing the temperature, humidity, precipitation, and crop type data, the central controller predicts the appropriate soil moisture value. This prediction relies on a predetermined algorithm or model.

The central controller uploads the predicted soil moisture value to the IoT cloud platform.

The Node MCU board retrieves the forecasted soil moisture value from the cloud.

By comparing the predicted soil moisture value with the current soil moisture level measured by its own sensors, the Node MCU board determines whether irrigation is necessary.

Before activating or deactivating the irrigation system, the Node MCU board assesses the value from an LDR (Light Dependent Resistor) sensor. This sensor measures the ambient light levels, aiding in distinguishing between day and night.

If it is daytime (indicated by the LDR sensor reading), and the predicted soil moisture value exceeds the current soil moisture level, the Node MCU board activates the irrigation system. This ensures adequate water supply to the crops during daylight hours.

If it is nighttime, the Node MCU board deactivates the irrigation system regardless of the predicted soil moisture value. This is because plants typically do not require irrigation during the night.

In summary, the system utilizes the Node MCU board equipped with a DHT11 sensor to gather temperature and humidity data, which is then transmitted to the ThingSpeak IoT cloud platform. The central controller, a Python program, retrieves this data alongside precipitation information and user input regarding the crop type. Based on these inputs, it predicts the necessary soil moisture value and uploads it to the IoT cloud. The Node MCU board retrieves this prediction, compares it with the current soil moisture level, and controls the irrigation system accordingly, while considering the LDR sensor's reading to determine whether it is day or night.



# Machine Learning

The Random Forest algorithm is known for its high accuracy and reliable predictions. It combines multiple decision trees created from different subsets of the dataset. By aggregating the predictions of each tree through majority voting, it improves the overall accuracy. Project is focused on training the model using four key climatic parameters and did not include specific agricultural inputs as they vary depending on the field.

Here, "farm model.pynb" file is the Trained model file for random forest algorithm. The  Dataset here is provided by the name "testst.csv".
"new.joblib" file is the trained model joblib file  and it is used by thee central controller too predict the values. 
