/**
 *  Modbus slave example 1:
 *  The purpose of this example is to link a data array
 *  from the Arduino to an external device.
 *
 *  Recommended Modbus Master: QModbus
 *  http://qmodbus.sourceforge.net/
 */

#include <ModbusRtu.h>
#include <SoftwareSerial.h>

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
Modbus slave(104,mySerial); // this is slave @1 and RS-232 or USB-FTDI

void setup() {
  Serial.begin(9600); // baud-rate at 19200
  mySerial.begin(9600);
  slave.start();
}

void loop() {
  slave.poll( au16data, 16 );
}
