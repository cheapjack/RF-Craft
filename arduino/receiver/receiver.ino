#include <RFM69.h>

#define SERIAL_BAUD    9600

#define NETWORKID         87
#define NODEID              254
#define REQUESTACK       true // whether to request ACKs for sent messages
#define ACK_TIME           50 // # of ms to wait for an ack

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
#ifdef IS_RFM69HW
  radio.setHighPower();
#endif
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
  }   
  
  while (Serial.available() > 0) {
    char character = Serial.peek();
    int code = Serial.parseInt();
    
    if (character == 'h') { 
      Serial.println(F("Accepted input"));
      Serial.println(F("(action),(node_id)"));
      Serial.println(F(" where action can be: "));
      Serial.println(F("-1,  query_id"));
      Serial.println(F(" 0, set_id"));
      Serial.println(F(" 1, button press"));
      Serial.println(F(" 2, error"));
      Serial.println(F(" 3, OK"));
    } else if (code == QUERY_ID) {
      int node = Serial.parseInt();
      Serial.println(NODEID);
    } else if (code == SET_ID) {
      int node = Serial.parseInt();
      Serial.println(F("currently unused"));
    } else if (code == BUTTON_PRESS) {
      int node = Serial.parseInt();
      Serial.println(F("we are the reciever already"));
    } else if (code == ERROR || code == OK) {
      int node = Serial.parseInt();
      if (node >= 1 && node <= 100) {   
        myPacket.action = code;
        myPacket.node = node;
        radio.send(myPacket.node, (const void*)(&myPacket), sizeof(myPacket), REQUESTACK);
        if (waitForAck()) {
          Serial.println(F("message recieved"));
        } else { 
          Serial.println(F("message lost to the ether"));
        }
      } else {
        Serial.print(F("unknown node: "));
        Serial.println(node);
      }
    } else { 
      Serial.print(F("unknown: "));
      Serial.println(code);
    }
    Serial.find("\n");
  }
}   

static bool waitForAck() 
{
  unsigned long now = millis();
  while (millis() - now <= ACK_TIME)
    if (radio.ACKReceived(myPacket.node))
      return true;
  return false;
}

