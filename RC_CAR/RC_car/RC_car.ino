#include <ESP8266WiFi.h>
#include<PubSubClient.h>

const char* mqtt_server="test.mosquitto.org";
WiFiClient espclient;
void callback(char* topic,byte* payload,unsigned int length1);
PubSubClient client(mqtt_server,1883,callback,espclient);


const int leftForward = D5;
const int leftBackward = D4;
const int rightForward = D0;
const int rightBackward = D2;


void setup() {
  pinMode(leftForward,OUTPUT);
  pinMode(leftBackward,OUTPUT);
  pinMode(rightForward,OUTPUT);
  pinMode(rightBackward,OUTPUT);
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
    
    if(payload[0]==49)
      {
        digitalWrite(leftForward,HIGH);
        digitalWrite(rightForward,HIGH);
        digitalWrite(leftBackward,LOW);
        digitalWrite(rightBackward,LOW);
      }
    else if(payload[0]==48)
      {
        digitalWrite(leftForward,LOW);
        digitalWrite(leftBackward,HIGH);
        digitalWrite(rightBackward,HIGH);
        digitalWrite(rightForward,LOW);
      }
    else if(payload[0]==51)
      {
        digitalWrite(leftForward,HIGH);
        digitalWrite(rightBackward,HIGH);
        digitalWrite(leftBackward,LOW);
        digitalWrite(rightForward,LOW);
      }
    else if(payload[0]==53)
      {
        digitalWrite(leftForward,LOW);
        digitalWrite(rightBackward,LOW);
        digitalWrite(leftBackward,HIGH);
        digitalWrite(rightForward,HIGH);
      }
     else if(payload[0]==54)
      {
        digitalWrite(leftForward,LOW);
        digitalWrite(rightBackward,LOW);
        digitalWrite(leftBackward,LOW);
        digitalWrite(rightForward,LOW);
      }
    
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
    client.subscribe("motorcontrol");
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
