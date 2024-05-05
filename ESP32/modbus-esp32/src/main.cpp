
// #ifdef ESP8266
//  #include <ESP8266WiFi.h>
// #else //ESP32
//  #include <WiFi.h>
// #endif
// #include <ModbusIP_ESP8266.h>

// //Modbus Registers Offsets
// const int LED_COIL = 100;
// //Used Pins
// const int ledPin = 0; //GPIO0

// //ModbusIP object
// ModbusIP mb;

// void setup() {
//   Serial.begin(115200);

//   WiFi.begin("U+NetFFFD", "1000001426");

//   while (WiFi.status() != WL_CONNECTED) {
//     delay(500);
//     Serial.print(".");
//   }

//   Serial.println("");
//   Serial.println("WiFi connected");
//   Serial.println("IP address: ");
//   Serial.println(WiFi.localIP());

//   mb.server();

//   pinMode(ledPin, OUTPUT);
//   mb.addCoil(LED_COIL);
// }

// void loop() {
//    //Call once inside loop() - all magic here
//    mb.task();

//    //Attach ledPin to LED_COIL register
//    digitalWrite(ledPin, mb.Coil(LED_COIL));
//    Serial.println(mb.Coil(LED_COIL));

//    delay(10);
// }

/*
  Modbus-Arduino Example - Test Analog Input (Modbus IP ESP8266)
  Read Analog sensor on Pin ADC (ADC input between 0 ... 1V)
  Original library
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino

  Current version
  (c)2017 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266
*/

// #ifdef ESP8266
//  #include <ESP8266WiFi.h>
// #else //ESP32
//  #include <WiFi.h>
// #endif
// #include <ModbusIP_ESP8266.h>

// //Modbus Registers Offsets
// const int SENSOR_IREG = 100;

// //ModbusIP object
// ModbusIP mb;

// long ts;

// void setup() {
//     Serial.begin(115200);

//     WiFi.begin("U+NetFFFD", "1000001426");
//     while (WiFi.status() != WL_CONNECTED) {
//         delay(500);
//         Serial.print(".");
//     }

//     Serial.println("");
//     Serial.println("WiFi connected");
//     Serial.println("IP address: ");
//     Serial.println(WiFi.localIP());

//     mb.server();		//Start Modbus IP
//     // Add SENSOR_IREG register - Use addIreg() for analog Inputs
//     mb.addIreg(SENSOR_IREG);

//     ts = millis();
// }

// void loop() {
//    //Call once inside loop() - all magic here
//    mb.task();

//    //Read each two seconds
//    if (millis() > ts + 2000) {
//        ts = millis();
//        //Setting raw value (0-1024)
//        mb.Ireg(SENSOR_IREG, analogRead(33));
//        Serial.println(mb.Ireg(SENSOR_IREG));
//    }
//    delay(10);
// }

#include <SPI.h>
#include <Ethernet.h> // Ethernet library v2 is required
#include <ModbusEthernet.h>

// Enter a MAC address and IP address for your controller below.
byte mac[] = {
    0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192, 168, 0, 100); // The IP address will be dependent on your local network:
ModbusEthernet mb;               // Declare ModbusTCP instance

const int SENSOR_IREG = 100;
long ts;

void setup()
{
    Serial.begin(115200);    // Open serial communications and wait for port to open
    Ethernet.init(5);        // SS pin
    Ethernet.begin(mac, ip); // start the Ethernet connection
    delay(1000);             // give the Ethernet shield a second to initialize
    mb.server();             // Act as Modbus TCP server
    // mb.addReg(HREG(100));    // Add Holding register #100
    mb.addIreg(SENSOR_IREG);
}

void loop() {
   //Call once inside loop() - all magic here
   mb.task();

   //Read each two seconds
   if (millis() > ts + 2000) {
       ts = millis();
       //Setting raw value (0-1024)
       mb.Ireg(SENSOR_IREG, analogRead(33));
       Serial.println(mb.Ireg(SENSOR_IREG));
   }
   delay(10);
}