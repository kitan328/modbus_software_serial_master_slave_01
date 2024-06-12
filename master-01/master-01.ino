#include <ModbusRtu.h>
#include <SoftwareSerial.h>

// data array for modbus network sharing
uint16_t au16data[16];
uint8_t u8state;

SoftwareSerial mySerial(3, 5);

/**
 *  Modbus object declaration
 *  u8id : node id = 0 for master, = 1..247 for slave
 *  port : serial port
 *  u8txenpin : 0 for RS-232 and USB-FTDI 
 *               or any pin number > 1 for RS-485
 */
Modbus master(0, mySerial); // this is master and RS-232 or USB-FTDI via software serial

/**
 * This is an structe which contains a query to an slave device
 */
modbus_t telegram;

unsigned long u32wait;

void setup() {
  Serial.begin(9600);
  Serial.println("Hellooo...");
  mySerial.begin(9600);//use the hardware serial if you want to connect to your computer via usb cable, etc.
  master.start(); // start the ModBus object.
  master.setTimeOut(2000); // if there is no answer in 2000 ms, roll over
  u32wait = millis() + 1000;
  u8state = 0; 
}

void loop() {
  switch( u8state ) {
  case 0: 
    if (millis() > u32wait) u8state++; // wait state
    break;
  case 1: 
    telegram.u8id = 104; // slave address
    telegram.u8fct = 4; // function code (this one is registers read)
    telegram.u16RegAdd = 0; // start address in slave
    telegram.u16CoilsNo = 1; // number of elements (coils or registers) to read
    telegram.au16reg = au16data; // pointer to a memory array in the Arduino

    master.query( telegram ); // send query (only once)
    u8state++;
    break;
  case 2:
    master.poll(); // check incoming messages
    if (master.getState() == COM_IDLE) {
      u8state = 0;
      u32wait = millis() + 2000;
        Serial.print("au16data[0] = "); 
        Serial.println(au16data[0]);//Or do something else!
    }
    break;
  }
}
