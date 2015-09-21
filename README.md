Button Craft
============

RFM69 radio buttons that report to a central reciever to perform minecraft actions

Message Format
--------------

messages are constructed of `int8_t` for action followed by a `uint8_t` for node_id. 

Possible messages:

 * -1 : query_id
 *  0 : set_id
 *  1 : button press
 *  2 : error
 *  3 : OK

common key for messages: "changemechangeme"

all radios are in group: 87

node_ids for buttons: 1-100

node_id for the receiver hub: 254
