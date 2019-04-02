/*
 * @author Tsonyo Vasilev
 * @version 0.6
 * 
 * version 0.6: Inherited from hs05_auto_atmode_2.ino
 * Code cleanup, first Processing visualzation, message format sent to 
 * Processing is <module address>;<temperature>;<humidity>
 * 
 * version 0.5: The code now uses an array of slave addresses,
 * pairs with them in sequence and stores their sensor readings.
 * 
 * version 0.4: Major changes to the connection algorithm -
 * PAIR, BIND and LINK commands are used in sequence to reliably connnect
 * to an HC-06 slave. Storing incoming readings as a String now uses a 
 * while loop.
 * 
 * version 0.3: Incoming sensor data is now stored  in a String variable
 * 
 * version 0.2: The code now sends a pairing confirmation message to the slave
 * and upon receiving it, HC-06 (slave) responds with temp + humidity readings from the DHT11 sensor
 * 
 *This sketch demonstrates how to connect an HC-05 Bluetooth module
 *used as a master to an HC-06 Bluetooth slave. The program automatically 
 *puts the HC-05 in AT mode, ready to accept commands and then pairs it with
 *an HC-06 slave with a known address. It then sends a message to the HC-06 via
 *Bluetooth connected to a different PC where the Arduino Serial Terminal displays it.
 *
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

//Needed for serial comms via Bluetooth
#include <SoftwareSerial.h>

#include <avr/wdt.h>

SoftwareSerial BTserial(2, 3); // RX | TX
// Connect the HC-05 TX to Arduino pin 3 RX. 
// Connect the HC-05 RX to Arduino pin 2 TX through a voltage divider (No voltage divider required, the board already has a regulator).

//D4 on the Arduino controls pin 34 on the HC-05 through a voltage divider, 
//dropping the output voltage to 3.3V rather than the 5V a digital pin supplies when pulled to HIGH.
byte atPin = 4;

//D7 turns the HC-05 on and off
byte hcPower = 7;

//D5 is connected to the STATE pin of the HC-05 and goes HIGH when the module is paired with a slave
byte pairedPin =5;

//Used for mirroring AT commands to the serial monitor
char c = ' ';

//This is a flag that is set to TRUE once HC-05 is in AT mode and ready for commands
bool isAtEngaged = 0;

//This is a flag that is set to TRUE once HC-05 has been paired with a slave
bool isPaired = 0;

//This variable will be used to store incoming sensor data
String incoming = "";

//Store slave addresses
String slave1 = "14,3,5593E";
String slave2 = "14,3,5597A";

//An array to hold slave addresses
String slaveArray [] = {"14,3,5593E", "14,3,5597A"};

unsigned long latestReadingTime = 0;


void setup() 
{
    // start the serial communication with the host computer
    Serial.begin(9600);
    //Serial.println("HC-05 and Arduino are ready, baud rate for comms with the PC is 9600.");
 
    // start communication with the HC-05 using 38400
    BTserial.begin(38400);  
    //Serial.println("BTserial started at 38400");

    //Pin 4 controls PIN 34 on the HC-05 through a voltage divider
    pinMode(atPin, OUTPUT);

    //Pin 7 powers the HC-05
    pinMode(hcPower, OUTPUT);
     
}

//Reset function
void(* resetFunc) (void) = 0;//declare reset function at address 0

void reboot() {
  wdt_disable();
  wdt_enable(WDTO_15MS);
  while (1) {}
}


//Call this to get the HC-05 into AT mode
void getATMode(){
    //Apply power to the HC-05
    digitalWrite(hcPower, HIGH); 
    delay(20);
    //Put the HC-05 in AT mode
    digitalWrite(atPin, HIGH); //Pin 34 to HIGH
    delay(100);
    digitalWrite(hcPower, LOW); //Disconnect power
    delay(200);
    digitalWrite(hcPower, HIGH); //Reconnect power
    delay(1500);
}

void connectToSlave(String slaveAddress){
  
    BTserial.write("AT+CMODE=0\r\n"); //Allow the HC-05 to connect to any device
    delay(400);
    
    BTserial.write("AT+INIT\r\n"); // Initiate SPP profile
    delay(400);
    
    BTserial.print("AT+PAIR=" + slaveAddress + ",9" + "\r\n");
    delay(4000);

    BTserial.print("AT+BIND=" + slaveAddress + "\r\n");
    delay(500);

    BTserial.print("AT+CMODE=1\r\n"); // Set HC-05 to only connect with paired devices
    delay(500);
    
    //14,3,5593E
    //14,3,5597A
    BTserial.print("AT+LINK="+slaveAddress+"\r\n"); //Link HC-05 to a slave
    
    delay(2000);
    
    digitalWrite(atPin, LOW); //Drive pin 34 low, we dont't need AT mode anymore
    isPaired = 1;   
    delay(400);
}

void loop(){
    
 for(byte k = 0; k < 2; k++){   
  /*
  //If it's been more than 35 seconds since the last reading,
  //reset the master
  if(millis()-latestReadingTime > 35000){
    Serial.println("Resetting...");
    latestReadingTime = 0;
    delay(500);
    reboot(); 
  }
  */
 //Switch HC-05 to AT mode in preparation for pairing
 //Set the isAtEngaged bool flag to true to make sure the getATMode function runs only once
  if(!isAtEngaged){
    getATMode();
    isAtEngaged = 1;
  }

  //HC-05 is now in АТ mode, ready to receive commands.
  //The lines that follow will send a series of AT commands
  //to pair HC-05 to a slave.
  if(!isPaired){

    //Connect to a slave with a specified address
    connectToSlave(slaveArray[k]);
    
    //Update the last time a reading was made
    //latestReadingTime = millis();
    //Serial.println("Latest reading time updated: " + latestReadingTime);

    //Send a welcome message to the slave 
    BTserial.print("\nConnected to master.\n");

    //When HC-05 is paired with a slave, the STATE pin is set to HIGH
    if(pairedPin){
      //Send a pairing confirmation message to the slave
      //Once received, it will respond with a temperature and humidity reading
      BTserial.print("P"); 
    } 

    //Loop until the message from the slave (starting with "T") is received, then store 
    //it in a String variable
    while(!incoming.startsWith("T")){
      //Store incoming data via BT to a string 
      incoming = BTserial.readString();
    
      //Uncomment to print debug messages
      //Serial.println(incoming.charAt(0));
      //Serial.println("Incomingstringis: "+incoming);
      //Serial.println("Incomingstringis STILL: "+incoming);
    }
    //Format a message to be printed to the SM
    //Processing picks this up and splits it for displaying
    Serial.println(slaveArray[k]+";"+incoming);

    //Reset the variable which stores incoming sensor readings
    incoming = "";
  }// end if  

  //Disable the AT bool before the next iteration
  isAtEngaged = 0;
  //Disable the paired bool before the next iteration
  isPaired = 0;
  //reset the string where readings are stored
  incoming = "";
 }//end main "for"
 
  delay(3000);
  
 }//end loop
  
