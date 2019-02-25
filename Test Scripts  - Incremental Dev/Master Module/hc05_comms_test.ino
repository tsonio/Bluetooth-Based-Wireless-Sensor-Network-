/*
 * @author Tsonyo Vasilev
 * @version 0.1
 *A simple sketch to test/demonstrate how to connect an HC-05 Bluetooth module
 *used as a master to an HC-06 Bluetooth slave. The module has to be
 *put into AT mode manually and then AT commands are typed in the 
 *Serial Monitor.
 */
 
//  Pins
//  BT VCC to Arduino 5V out. 
//  BT GND to GND
//  BT RX to Arduino pin 3 (through a voltage divider)
//  BT TX to Arduino pin 2 (no need voltage divider)

//HOW TO GET THE BOARD IN AT MODE FOR DUMMIES:
//1. Connect everything according to the pinout above
//2. Press and HOLD the button on the BT board connected to Pin 34
//3. Unplug the jumper that connects the module to the power rail on the Arduino (5V pin)
//4. While holding the button, reconnect the module to the 5V output
//5. The LED on the BT board starts flashing slowly (~every 2 seconds)
//6. The module is now in AT mode, yay!!!!

 
 
#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 11 RX. 
// Connect the HC-05 RX to Arduino pin 10 TX through a voltage divider (No voltage divider required, the board already has a regulator).
 
char c = ' ';
 
void setup() 
{
    // start th serial communication with the host computer
    Serial.begin(9600);
    Serial.println("Arduino with HC-05 is ready");
 
    // start communication with the HC-05 using 38400
    BTserial.begin(38400);  
    Serial.println("BTserial started at 38400");
}
 
void loop()
{
 
     // Keep reading from HC-05 and send to Arduino Serial Monitor
    if (BTserial.available())
    {  
        c = BTserial.read();
        Serial.write(c);
    }
 
    // Keep reading from Arduino Serial Monitor and send to HC-05
    if (Serial.available())
    {
        c =  Serial.read();
 
        // mirror the commands back to the serial monitor
        // makes it easy to follow the commands
        Serial.write(c);   
        BTserial.write(c);  
    }
 
}
