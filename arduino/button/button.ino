#include <RFM69.h>
#include <EEPROM.h>
#include <avr/power.h>
#include <avr/sleep.h>

#define SERIAL_PRINT         1 //choose serial reporting on (1) or off (0)
#define SERIAL_BAUD       9600

#define NETWORKID           87
#define NODEID               1 // 1-100 for nodes
#define NODEID_LOCATION     78
#define GATEWAYID          254
#define FREQUENCY  RF69_868MHZ
#define IS_RFM69HW
#define REQUESTACK        true // whether to request ACKs for sent messages
#define ACK_TIME            50 // # of ms to wait for an ack
#define LISTEN_FOR_REPLY  true // choose if we want to listen and parse a reply
#define WAIT_FOR_REPLY 10000UL // how long should we wait for a reply before going back to sleep?

byte this_node_id = NODEID;

#define LED                  9
#define BUTTON            INT1 // choose an interrupt pin

#define DBOUNCE_TMOUT    500UL
#define LED_TIMEOUT    12000UL
#define SLEEP_TIMEOUT   1000UL

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
Payload myPacket;
Payload yourPacket;

RFM69 radio;

unsigned long lastSend = 0;
unsigned long lastButton = 0;
unsigned long lastAction = 0;
volatile boolean button = false;
volatile boolean radioCalled = true;

byte isButton(byte k_node_id = this_node_id)
{
  if (k_node_id >= 1 && k_node_id <= 100) {
    return true;
  } else {
    return false;
  }
}

byte isGateway(byte k_node_id = this_node_id)
{
  if (k_node_id == 254) {
    return true;
  } else {
    return false;
  }
}

void setup()
{
  // set up ports for minimal leakage current
  DDRD &= B00000011;       // set Arduino pins 2 to 7 as inputs, leaves 0 & 1 (RX & TX) as is
  DDRB = B00000000;        // set pins 8 to 13 as inputs
  PORTD |= B11111100;      // enable pullups on pins 2 to 7
  PORTB |= B11111111;      // enable pullups on pins 8 to 13
#if SERIAL_PRINT == 1
  Serial.begin(SERIAL_BAUD);
#endif
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  pinMode(BUTTON, INPUT);
  digitalWrite(9, LOW);

  radio.initialize(FREQUENCY, NODEID, NETWORKID);
#ifdef IS_RFM69HW
  radio.setHighPower();
#endif
  radio.encrypt(ENCRYPTKEY);
  radio.sleep(); //sleep right away to save power

  byte node;
  EEPROM.get(NODEID_LOCATION, node);
  if (isButton(node) || isGateway(node)) {
    this_node_id = node;
  } else {
    this_node_id = NODEID;
  }
  myPacket.node = this_node_id;
  myPacket.action = 0;

  attachInterrupt(BUTTON, buttonCheck, FALLING);
#if SERIAL_PRINT == 1
  Serial.println("Ready...");
#endif
}

void loop()
{
  while (Serial.available() > 0) {
    char character = Serial.peek();
    int code = Serial.parseInt();

    if (character == 'h') {
      Serial.println(F("Accepted input"));
      Serial.println(F("(action),(node_id)"));
      Serial.println(F("where action can be: "));
      Serial.println(F("-1, set_id"));
      Serial.println(F(" 0, query_id"));
      Serial.println(F(" 1, button press"));
      Serial.println(F(" 2, error"));
      Serial.println(F(" 3, OK"));
      Serial.println(F("and node_id can be: "));
      Serial.println(F(" 1-100 for buttons"));
      Serial.println(F(" 254 for the gateway"));
    } else if (code == QUERY_ID) {
      Serial.print(F("NODEID: "));
      Serial.println(this_node_id);
    } else if (code == SET_ID) {
      int node = Serial.parseInt();
      if (isButton(node) || isGateway(node)) {
        this_node_id = node;
        EEPROM.put(NODEID_LOCATION, this_node_id);
        radio.initialize(FREQUENCY, this_node_id, NETWORKID);
      }
      Serial.print(F("NODEID: "));
      Serial.println(this_node_id);
    } else if (code == BUTTON_PRESS) {
      if (isGateway()) {
        Serial.println(F("NOT_A_BUTTON"));
      } else {
        button = true;
      }
    } else if (code == ERROR || code == OK) {
      int node = Serial.parseInt();
      if (isButton(node)) {
        myPacket.action = code;
        myPacket.node = node;
        radio.send(myPacket.node, (const void*)(&myPacket), sizeof(myPacket), REQUESTACK);
        if (waitForAck()) {
          Serial.println(F("ACK"));
        } else {
          Serial.println(F("NAK"));
        }
      } else {
        Serial.print(F("NON"));
        Serial.println(node);
      }
    } else {
      Serial.print(F("ERROR: "));
      Serial.println(code);
    }
    Serial.find("\n");
  }

  if (isButton()) {
    //on button press,
    if (radioCalled == false) {
      lastAction = millis();
      //make a radio call
      myPacket.action = BUTTON_PRESS;
      detachInterrupt(BUTTON);
#if SERIAL_PRINT == 1
      Serial.print("Calling... ");
      Serial.print(myPacket.node);
      Serial.print(":");
      Serial.print(myPacket.action);
#endif
      radio.send(GATEWAYID, (const void*)(&myPacket), sizeof(myPacket), REQUESTACK);
      radioCalled = true;
      boolean listen_for_reply = LISTEN_FOR_REPLY;
      if (REQUESTACK) {
#if SERIAL_PRINT == 1
        Serial.print(" - waiting for ACK...");
#endif
        if (waitForAck()) {
#if SERIAL_PRINT == 1
          Serial.print("ok!");
#endif
          // pulse the onboard led
          morseLed(ACK);
          lastAction = millis();
          //pulseLed(LED_TIMEOUT);
          digitalWrite(LED, LOW);
          //button = false;
        } else {
#if SERIAL_PRINT == 1
          Serial.print("no reply...");
#endif
          button = false;
          lastAction = millis();
          morseLed(NAK);
          listen_for_reply = false;
        }
        if (listen_for_reply == true) {
          unsigned long reply_time = millis();
          boolean replied = false;
          while (millis() - reply_time <= WAIT_FOR_REPLY) {
            //digitalWrite(LED, HIGH);
            if (radio.receiveDone()) {
              //digitalWrite(LED, LOW);
              if (radio.DATALEN != sizeof(yourPacket)) {
#if SERIAL_PRINT == 1
                Serial.print("Invalid payload recieved");
#endif
                morseLed(NON);
              } else {
                replied = true;
                yourPacket = *(Payload*)radio.DATA;
#if SERIAL_PRINT == 1
                Serial.print("Recieved: ");
                Serial.print(yourPacket.node);
                Serial.print(":");
                Serial.print(yourPacket.action);
                Serial.println();
#endif
              }
              if (radio.ACKRequested()) {
                radio.sendACK();
#if SERIAL_PRINT == 1
                Serial.println("ACK sent");
#endif
              }
              break;
            }
          }
          if (replied == true) {
            if (yourPacket.action == OK) {
              Serial.print("received OK");
              morseLed(OK);
              gap();
              pulseLed(LED_TIMEOUT);
            } else {
              Serial.print("received: ");
              Serial.print(yourPacket.action);
              morseLed(yourPacket.action);
            }
          } else {
#if SERIAL_PRINT == 1
            Serial.print("no message: ");
#endif
            morseLed(NO_DATA);
          }
          digitalWrite(LED, LOW);
        }
      }
      button = false;
      radio.sleep();
      attachInterrupt(BUTTON, buttonCheck, FALLING);
#if SERIAL_PRINT == 1
      Serial.println();
#endif
    lastAction = millis();
    }

    // reduce battery consumption with sleep mode
    //if (millis() - lastAction >= SLEEP_TIMEOUT) {
//#if SERIAL_PRINT == 1
      //Serial.print("Sleeping...zzz...");
      //delay(100);
//#endif
      //set_sleep_mode(SLEEP_MODE_STANDBY);
      //sleep_enable();
      //sleep_mode();
      //sleep_disable();
//#if SERIAL_PRINT == 1
      //Serial.println(" Awake!");
//#endif
      //lastAction = millis();
    //}
  }// end of isButton
}

static bool waitForAck()
{
  unsigned long now = millis();
  while (millis() - now <= ACK_TIME)
    if (radio.ACKReceived(GATEWAYID))
      return true;
  return false;
}

void buttonCheck()
{
  // interrupt function for button
  // check for debounce timeout
  if (millis() - lastButton >= DBOUNCE_TMOUT) {
    lastButton = millis();
    button = !button;
    radioCalled = false;
  }
}

void pulseLed(unsigned long time)
{
  unsigned long startTime = millis();
  while (millis() - startTime <= (unsigned long)time && button == true) {
      float val = (exp(sin((millis()-startTime)/1000.0*PI)) - 0.36787944)*108.0;
      analogWrite(LED, val);
  }
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
