#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include "DHT.h"

int xPin = A0;    //x-axis of the Accelerometer 
//const int xPin = A0;    //x-axis of the Accelerometer 
String B;

DHT dht;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const char* ssid = "SLT-4G-C74A";
const char* password =  "222864Y077N";
// 
//const char* ssid = "SLT_FIBRE";
//const char* password =  "SLT_FIBRE";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);


void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) 
    {
      Serial.println("connected");
    } else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() 
{
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  mlx.begin(); 
  dht.setup(D5); 
}

void loop() 
{
 int x = analogRead(xPin);
 String vib = String(x); 
 //int num = mlx.readObjectTempC();
 int num = 25;
 String tmp = String(num);
 //int humidity = dht.getHumidity();
 int humidity = 36;
 String hum = String(humidity); 

 String topic = "SLT_IIoT/A_0001/d_0001/sensor"; 


String data = topic + "," + vib + "," + tmp + "," + hum;
//String data = vib + "," + tmp + "," + hum;
int str_len = data.length() + 1; 
char publishing[50];
data.toCharArray(publishing, str_len);

//String data = vib + tmp + hum;
//int str_len = data.length() + 1; 
//char publishing[50];
//data.toCharArray(publishing, str_len);

//  int x = analogRead(xPin);
//    String svib;
//    svib = String(x);   //Converts integer to string
//    Serial.println(svib); 
//      
// int num = 50;
//    String stmp;
//    stmp = String(num);   //Converts integer to string
//    Serial.println(stmp); 
//      
// int humidity = 20;
//    String shum;
//    shum = String(humidity);   //Converts integer to string
//    Serial.println(shum); 

 //B ="svib," + stmp, + "shum";

// int num = mlx.readObjectTempC();
//      char tmp[16];
//      itoa(num, tmp, 10);
//      Serial.println(tmp); 
//      
// int humidity = dht.getHumidity();/* Get humidity value */
//      //int hum = humidity;
//      char hum[16];
//      itoa(humidity, hum, 10);
//      Serial.println(hum); 
  
   if (!client.connected()) 
    {
      reconnect();
    }
      client.loop();

      
  client.publish("SLT_IIoT/A_0001/d_0001/sensor", publishing);
//   client.publish("SLT_IIoT/A_0001/d_0001/tmp", tmp);
//   client.publish("SLT_IIoT/A_0001/d_0001/hum", hum);
   delay(1000);

}



// int myInts[6];


//  int myPins[] = {x, num, humidity};
//  
//
// for (int i=0; i<3; i++) 
//   {
//    int myPins[i];
//    String myStr;
//    myStr = String(myPins[i]);   //Converts integer to string
//    Serial.println(myStr); 
//    B ="Data/" + myStr + "/";
//   }
//   Serial.println(B);
