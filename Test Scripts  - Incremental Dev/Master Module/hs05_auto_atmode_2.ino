/*
 * @author Tsonyo Vasilev
 * @version 0.1
 *This sketch demonstrates how to connect an HC-05 Bluetooth module
 *used as a master to an HC-06 Bluetooth slave. The program automatically 
 *puts the HC-05 in AT mode, ready to accept commands and then pairs it with
 *an HC-06 slave with a known address. It then sends a message to the HC-06 via
 *Bluetooth connected to a different PC where the Arduino Serial Terminal displays it.
 */
//  Pins
//  BT VCC to Arduino 5V out. 
//  BT GND to GND
//  BT RX to Arduino pin 3 (through a voltage divider)
//  BT TX to Arduino pin 2 (no need voltage divider)

//HOW TO GET THE BOARD IN AT MODE FOR DUMMIES:
//This sketch puts HC-05 in AT mode automatically when the mC is powered up.
//1. Connect everything according to the pinout above
//2. Press and HOLD the button on the BT board connected to Pin 34
//3. Unplug the jumper that connects the module to the power rail on the Arduino (5V pin)
//4. While holding the button, reconnect the module to the 5V output
//5. The LED on the BT board starts flashing slowly (~every 2 seconds)
//6. The module is now in AT mode, yay!!!!

 
 
#include <SoftwareSerial.h>
SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 3 RX. 
// Connect the HC-05 RX to Arduino pin 2 TX through a voltage divider (No voltage divider required, the board already has a regulator).

//D4 on the Arduino controls pin 34 on the HC-05 through a voltage divider, 
//dropping the output voltage to 3.3V rather than the 5V a digital pin supplies when pulled to HIGH.
byte atPin = 4;

//D7 turns the HC-05 on and off
byte hcPower = 7;

//Used for mirroring AT commands to the serial monitor
char c = ' ';

//This is a flag that is set to TRUE once HC-05 is in AT mode and ready for commands
bool isAtEngaged = 0;

//This is a flag that is set to TRUE once HC-05 has been paired with a slave
bool isPaired = 0;

void setup() 
{
    // start the serial communication with the host computer
    Serial.begin(9600);
    Serial.println("HC-05 and Arduino are ready, baud rate for comms with the PC is 9600.");
 
    // start communication with the HC-05 using 38400
    BTserial.begin(38400);  
    Serial.println("BTserial started at 38400");

    //Pin 4 controls PIN 34 on the HC-05 through a voltage divider
    pinMode(atPin, OUTPUT);

    //Pin 7 powers the HC-05
    pinMode(hcPower, OUTPUT);

  
    
}

//Call this to get the HC-05 into AT mode
void getATMode(){
    digitalWrite(hcPower, HIGH); 
    delay(20);
    //Get the HC-05 to AT mode
    digitalWrite(atPin, HIGH); //Pin 34 to HIGH
    delay(100);
    digitalWrite(hcPower, LOW); //Disconnect power
    delay(200);
    digitalWrite(hcPower, HIGH); //Reconnect power
    delay(1500);
}

void loop(){
 
     // Read from HC-05 and send to the Serial Monitor
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
        Serial.write(c);   
        BTserial.write(c);  
    }

 //Switch HC-05 to AT mode in preparation for pairing
 //Set the isAtEngaged bool flag to true to make sure the getATMode function runs only once
  if(!isAtEngaged){
    getATMode();
    isAtEngaged = 1;
  }

  //HC-05 is now in pairing mode.
  //The lines that follow will send a series of AT commands
  //to pair HC-05 to a slave.
  if(!isPaired){
    BTserial.write("AT\r\n"); //The HC-05 responds with "OK" if everything's fine. 
    delay(20);
    BTserial.write("AT+INIT\r\n");
    delay(20);
    BTserial.write("AT+PAIR=14,3,5593E,9\r\n");
    delay(100);
    digitalWrite(atPin, LOW);
    isPaired = 1;   

   //Send a message to the slave 
    BTserial.write("HELLO THERE!\n");
    delay(3000);
  } 

 }//end loop
  
