
 // Including library for dht

#include <ESP8266WiFi.h>
 int i=0;
 int n=1;
String apiKey = "TNN596D84LIUE9A8";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "LT-BW-IN-01";     // replace with your wifi ssid and wpa2 key
const char *pass =  "Raj995si";
const char* server = "api.thingspeak.com";

#define DHTPIN D8         //pin where the dht11 is connected

WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);
     
 
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
 
}
 
void loop() 
{
  delay(5000);
      
      if(digitalRead(D8)==0)
      {
        i++;
        Serial.println(i);
    
if(i>n*10)
{
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(i);
                             postStr +="&field2=";
                             postStr += String(i);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
                             n++;
 
                          
                      } }}
          client.stop();
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
}

