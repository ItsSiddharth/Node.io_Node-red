#include <ESP8266WiFi.h>
#include<PubSubClient.h>

const char* mqtt_server="test.mosquitto.org";
WiFiClient espclient;
void callback(char* topic,byte* payload,unsigned int length1);
PubSubClient client(mqtt_server,1883,callback,espclient);

#define LED D2
int brightness;

void setup() {
  
   pinMode(D2,OUTPUT);
  Serial.begin(115200);
  Serial.print("connecting");
  WiFi.begin("siddharth","siddharth");         //SSID,PASSWORD 
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  
  reconnect();
  

}


void callback(char* topic,byte* payload,unsigned int length1){    
Serial.print("message arrived[");
Serial.print(topic);
Serial.println("]");

for(int i=0;i<length1;i++){
  Serial.print(payload[i]); 
  
}
brightness = map(payload[0], 48, 57, 0, 255);
analogWrite(LED,brightness);

Serial.println();
}


void reconnect(){
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  while(!client.connected()){
  if(client.connect("ESP8266Client123456789")){
    Serial.println("connected");
    client.subscribe("ledslider");
  }
    else{
      Serial.print("failed,rc=");
      Serial.println(client.state());
      delay(500);
    }
  } 
}
void loop() {
    if(!client.connected()){
      reconnect();
    }
    
    client.loop();

}
