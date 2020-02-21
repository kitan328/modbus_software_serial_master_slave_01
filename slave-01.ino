#include <ModbusRtu.h>
#include <SoftwareSerial.h>

#define SWITCH_PIN 4

// data array for modbus network sharing
uint16_t au16data[16] = {
  11, 1415, 9265, 7, 2, 7182, 28182, 8, 0, 0, 0, 0, 0, 0, 1, -1 };

SoftwareSerial mySerial(3, 5);
/**
 *  Modbus object declaration
 *  u8id : node id = 0 for master, = 1..247 for slave
 *  port : serial port
 *  u8txenpin : 0 for RS-232 and USB-FTDI 
 *               or any pin number > 1 for RS-485
 */
Modbus slave(104, mySerial); // this is slave @1 and RS-232 or USB-FTDI

void setup() {
  // input pin
  pinMode(SWITCH_PIN, INPUT);
  
  // for debug
  Serial.begin(9600);
  
  // for send data
  mySerial.begin(9600);
  
  slave.start();
}

void loop() {
  slave.poll(au16data, 16);
  
  // check data from master
    // If the master device sets the first element in the array to 0, turn off the LED.
  // Any other number will make the LED go high.
  if (au16data[1] == 0) {
    digitalWrite(LED_PIN, LOW);
  } else {
    digitalWrite(LED_PIN, HIGH);
  }
 
  // Set the second element in the array to the state of the switch
  au16data[2] = digitalRead(SWITCH_PIN);
}
