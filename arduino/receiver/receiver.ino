#include <SPI.h>
#include <RFM69.h>

#define SERIAL_BAUD    9600

#define NETWORKID         87
#define NODEID              254
#define REQUESTACK       true // whether to request ACKs for sent messages
#define ACK_TIME           50 // # of ms to wait for an ack

byte this_node_id = NODEID;

#define LED                  9
#define BUTTON            INT1 // choose an interrupt pin

#define FREQUENCY RF69_868MHZ
#define IS_RFM69HW

#define DOT              200UL
#define DASH             600UL // DOT*3

#define QUERY_ID             0
#define SET_ID              -1
#define BUTTON_PRESS         1
#define ERROR                2
#define OK                   3
#define ACK                  4
#define NAK                  5
#define NON                  6
#define NO_DATA              7

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
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  pinMode(BUTTON, INPUT);

  radio.initialize(FREQUENCY, this_node_id, NETWORKID);
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
      Serial.println(F("-1, set_id"));
      Serial.println(F(" 0, query_id"));
      Serial.println(F(" 1, button press"));
      Serial.println(F(" 2, error"));
      Serial.println(F(" 3, OK"));
    } else if (code == QUERY_ID) {
      int node = Serial.parseInt();
      Serial.println(this_node_id);
    } else if (code == SET_ID) {
      int node = Serial.parseInt();
      if ((node >= 1 && node <= 100) || node == 254) {
        this_node_id = node;
        radio.initialize(FREQUENCY, this_node_id, NETWORKID);
      }
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
          Serial.println(F("ACK"));
          morseLed(ACK);
        } else {
          Serial.println(F("NAK"));
          morseLed(NAK);
        }
      } else {
        Serial.print(F("NAN"));
        Serial.println(node);
        morseLed(NON);
      }
    } else {
      Serial.print(F("ERROR: "));
      Serial.println(code);
      morseLed(NO_DATA);
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

void morseLed(byte k_message)
{
  if (k_message == ERROR) {
    // E
    dot();
    gap();
    // R
    dot(); dash(); dot();
    gap();
    // R
    dot(); dash(); dot();
  } else if (k_message == OK) {
    // O
    dash(); dash(); dash();
    gap();
    // K
    dash(); dash(); dash();
  } else if (k_message == ACK) {
    // A
    dot(); dash();
    gap();
    // C
    dash(); dot(); dash(); dot();
    gap();
    // K
    dash(); dot(); dash();
  } else if (k_message == NAK) {
    // N
    dash(); dot();
    gap();
    // A
    dot(); dash();
    gap();
    // K
    dash(); dot(); dash();
  } else if (k_message == NON) {
    // N
    dash(); dot();
    // A
    dot(); dash();
    // N
    dash(); dot();
  } else if (k_message == NO_DATA) {
    // N
    dash(); dot();
    // O
    dash(); dash(); dash();
    // D
    dash(); dot(); dot();
    // A
    dot(); dash();
    // T
    dash();
    // A
    dot(); dash();
  } else {
    // ?
    dot(); dot(); dash(); dash(); dot(); dot();
  }
}

void dot()
{
  digitalWrite(LED, HIGH);
  delay(DOT);
  digitalWrite(LED, LOW);
  delay(DOT);
}

void dash()
{
  digitalWrite(LED, HIGH);
  delay(DASH);
  digitalWrite(LED, LOW);
  delay(DOT);
}

void gap()
{
  // space is normally 3*DOT, but each dot/dash ends in
  // a single dot length delay.
  delay(DOT*2);
}

void space()
{
  delay(DOT*6);
}
