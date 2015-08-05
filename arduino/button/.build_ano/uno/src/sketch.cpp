#include <Arduino.h>
#include <RFM69.h>
#include <avr/power.h>
#include <avr/sleep.h>
void setup();
void loop();
static bool waitForAck();
void buttonCheck();
void pulseLed(unsigned long time);
#line 1 "src/sketch.ino"
//#include <RFM69.h>
//#include <avr/power.h>
//#include <avr/sleep.h>

#define SERIAL_PRINT        1 //choose serial reporting on (1) or off (0)
#define SERIAL_BAUD    9600

#define NETWORKID         87
#define NODEID              1 // 1-100 for nodes
#define GATEWAYID           254 
#define FREQUENCY RF69_868MHZ
#define IS_RFM69HW
#define REQUESTACK       true // whether to request ACKs for sent messages
#define ACK_TIME           50 // # of ms to wait for an ack
#define LISTEN_FOR_REPLY true // choose if we want to listen and parse a reply
#define WAIT_FOR_REPLY 10000UL // how long should we wait for a reply before going back to sleep?

#define LED                 9
#define BUTTON           INT1 // choose an interrupt pin 

#define DBOUNCE_TMOUT   500UL
#define LED_TIMEOUT   12000UL
#define SLEEP_TIMEOUT  1000UL

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
Payload myPacket;
Payload yourPacket;

RFM69 radio;

unsigned long lastSend = 0;
unsigned long lastButton = 0;
unsigned long lastAction = 0;
volatile boolean button = false;
volatile boolean radioCalled = true;

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

  myPacket.node = NODEID;
  myPacket.action = 0;
  
  attachInterrupt(BUTTON, buttonCheck, FALLING);
#if SERIAL_PRINT == 1
  Serial.println("Ready...");
#endif
}

void loop() 
{
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
    if (REQUESTACK) {
#if SERIAL_PRINT == 1
      Serial.print(" - waiting for ACK...");
#endif
      if (waitForAck()) {
#if SERIAL_PRINT == 1
        Serial.print("ok!");
#endif
        // pulse the onboard led
        lastAction = millis();
        //pulseLed(LED_TIMEOUT);
        digitalWrite(LED, LOW);
        //button = false;
      }
      else {
#if SERIAL_PRINT == 1
        Serial.print("no reply...");
#endif
        button = false;
        digitalWrite(LED, HIGH);
        lastAction = millis();
        delay(100);
        digitalWrite(LED, LOW);
      }
      if (LISTEN_FOR_REPLY == true) {
        unsigned long reply_time = millis();
        boolean replied = false;
        while (millis() - reply_time <= WAIT_FOR_REPLY) {
          digitalWrite(LED, HIGH);
          if (radio.receiveDone()) {
            digitalWrite(LED, LOW);
            if (radio.DATALEN != sizeof(yourPacket)) {
#if SERIAL_PRINT == 1
              Serial.print("Invalid payload recieved");
#endif
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
        if (replied == true && yourPacket.action == OK) {
          Serial.print("received OK");
          pulseLed(LED_TIMEOUT);
        } else {
#if SERIAL_PRINT == 1
          Serial.print("no message: ");
          Serial.print(yourPacket.action);
#endif
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
  
  if (millis() - lastAction >= SLEEP_TIMEOUT) {
#if SERIAL_PRINT == 1
    Serial.print("Sleeping...zzz...");
    delay(100);
#endif
    set_sleep_mode(SLEEP_MODE_STANDBY);
    sleep_enable();
    sleep_mode();
    sleep_disable();
#if SERIAL_PRINT == 1
    Serial.println(" Awake!");
#endif
    lastAction = millis();
  }
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

