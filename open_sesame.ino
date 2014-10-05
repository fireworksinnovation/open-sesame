
#include <SPI.h>
#include <Ethernet.h>
#include "string.h"
#include "iotconnector.h"

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetClient client;

char pubkey[] = "pub-****************";
char subkey[] = "sub-****************";
char channel[] = "****";
char uuid[] = "Arduino";

int solinoidPin = 7;
 
iotbridge arduino;
 
void initialize(){
  Serial.begin(9600);
  Serial.println("Serial set up");
 
  while (!Ethernet.begin(mac)) {
    Serial.println("Ethernet setup error");
    delay(1000);
  }
  Serial.println("Ethernet set up");
}

void handleMessage(String value){
  String message = "[\"open\"]";
  if(value == message)
  {
    //Publish
    arduino.send(channel,"\"You may enter\"");
    openSwitch();
  }
}

void setup()
{
  initialize();
  arduino.init( pubkey, subkey, uuid);
  
  pinMode(solinoidPin, OUTPUT);
}
 
void loop()
{
  String message;
  Ethernet.maintain();
  
  //Subscribe
  message = arduino.connect(channel);
  
  //callback function of sorts, to work with the received message
  handleMessage(message);
}

void openSwitch(){
  digitalWrite(solinoidPin, HIGH);
  //wait 10 seconds before engaging the magnetic latch
  delay(10000);
  digitalWrite(solinoidPin, LOW);
}
