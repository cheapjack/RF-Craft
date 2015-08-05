#include <Arduino.h>
#include <RFM69.h>
void setup();
void loop();
#line 1 "src/sketch.ino"
//#include <RFM69.h>

#define SERIAL_BAUD    9600

#define NETWORKID         87
#define NODEID              254
#define REQUESTACK       true // whether to request ACKs for sent messages
#
#define FREQUENCY RF69_868MHZ
#define IS_RFM69HW

#define QUERY_ID -1
#define SET_ID 0
#define BUTTON_PRESS 1
#define ERROR 2
#define OK 3

#define ENCRYPTKEY "changemechangeme"

typedef struct { 
  uint8_t action;
  uint8_t node;
} Payload;
Payload theData;
Payload myPacket;

RFM69 radio;

void setup() 
{
  Serial.begin(SERIAL_BAUD);

  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.encrypt(ENCRYPTKEY);
}

void loop() 
{
  if (radio.receiveDone() && radio.DATALEN == sizeof(Payload)) {
    theData = *(Payload*)radio.DATA;
    Serial.print(theData.node);
    Serial.print(",");
    Serial.print(theData.action);
    Serial.println();
    if (radio.ACKRequested()) {
      radio.sendACK();
    }
    
    if (theData.action == BUTTON_PRESS) {
      Serial.print("Sending: ");
      myPacket.node = theData.node;
      myPacket.action = OK;
      Serial.print(myPacket.node);
      Serial.print(myPacket.action);
      Serial.println();
      radio.send(theData.node, (const void*)(&myPacket), sizeof(myPacket), REQUESTACK);
    }
  }   
}

