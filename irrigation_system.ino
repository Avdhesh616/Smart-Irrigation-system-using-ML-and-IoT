#include <DHT.h>  // Including library for dht
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include<ThingSpeak.h>

// CHECK THE NODE MCU PIN CONFIGURATION 
#define LED 14 
#define ldr 16

const char *RapiKey = "..........";     //  Enter your Read API key from ThingSpeak
String WapiKey = ".............";     //  Enter your Write API key from ThingSpeak
 
  // channe Details-----
unsigned long channelID = ........;    // Channel Id 
const char *ssid =  "WIFI_SSID";     // replace with your wifi ssid and wpa2 key
const char *pass =  "WIFI_PASS";
const char* host = "api.thingspeak.com";
unsigned int fieldNumber = ; //PROVIDE YOUR FIELD NUMBER 
const int updateInterval = 15000;  // Update interval in milliseconds

WiFiClient client;
WiFiClient client2;

#define DHTPIN 4          //pin where the dht11 is connected
 
DHT dht(DHTPIN, DHT11);



int moisture_Pin= 0; // Soil Moisture Sensor input at Analog PIN A0
 

 
void setup() 
{
       Serial.begin(115200);
       delay(10);
       dht.begin();

       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
    ThingSpeak.begin(client2);
    pinMode(ldr,INPUT);
    pinMode(LED, OUTPUT);    // LED pin as output.

}





void upload_data()
{
        float h = dht.readHumidity();
      float t = dht.readTemperature();
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
 
                         if (client.connect(host,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = WapiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+WapiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.println("%. Publishing to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
}

 
void loop() 
{
      int sdata = digitalRead (ldr);
      upload_data();
      delay(15);
      float value = fetchdata();
      Serial.print("Required soil moisture value: ");
      Serial.println(value);

      float curr_moisture = read_moisture();  // Read moisture data

      Serial.println("LDR Sensor value:   ");
      Serial.print(sdata);
      Serial.println();
      
      if(curr_moisture<value){
        Serial.print("Current soil moisture value is less than required soil mositure.");
        if (sdata == 1){
          Serial.println("It is night");
        digitalWrite(LED, LOW);
        Serial.println("Its night no need for irrigation....... MOTOR OFF!!!!!!!");
          }
          else
          {
                Serial.println("It is day");
                digitalWrite(LED, HIGH); // turn the LED on.
                Serial.println("!!!!! MOTOR ON !!!!!!!");
          }
      }
      else
        {
          Serial.print("Current soil moisture value is not less than required soil mositure.");
           Serial.println("Sufficient water in the field ...... MOTOR OFF!!!!!!!");
           digitalWrite(LED, LOW);            //Initially LED is turned off
        }
  // thingspeak needs minimum 15 sec delay between updates
  delay(10000);
}


float read_moisture(){
    float moisture_value=( 100.00 - ( (analogRead(moisture_Pin)/1023.00) * 100.00 ) );
    Serial.print("Current soil moisture value:");
    Serial.println(moisture_value);
    return moisture_value;
}

float fetchdata()
{
  float value = ThingSpeak.readFloatField( channelID, fieldNumber, RapiKey );                                                          
  return value;
}
