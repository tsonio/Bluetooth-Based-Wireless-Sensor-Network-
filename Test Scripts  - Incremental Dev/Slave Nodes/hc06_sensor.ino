//Required by the DHT sensor library, otherwise the code does not comile
#include <Adafruit_Sensor.h>

//DHT sensor library
#include <DHT.h>
#include <DHT_U.h>

//Required for serial comms
#include <SoftwareSerial.h>

//  A basic sketch to test the BT connection between an HC-06 slave and an HC-05 master.
//  It also reads temperature and humidity values from a DHT11 sensor and sends it to the master
//  Uses hardware serial to talk to the host computer and software serial for communication with the bluetooth module
//
//  PINOUT:
//  BT VCC to 5V out 
//  BT GND to GND
//  BT RX to Arduino pin 11 
//  BT TX to Arduino pin 10 
//
//  When a command is entered in the serial monitor on the computer 
//  the Arduino will relay it to the bluetooth module and display the result.
//
 

//Store temperature and humidity values
float temperature;
float humidity;

//The DHT library returns an object containing both readings

//Data pin for the DHT11 sensor
byte sensorPin = 7;

//Create a DHT object
DHT dht(sensorPin, DHT11);

SoftwareSerial BTSerial(10, 11); // RX | TX
 
void setup() 
{
    //Start the serial connection to the HC-06
    Serial.begin(9600);
    Serial.println("HC-06 ready");
    Serial.println("DHT11 sensor ready");
 
    // HC-06 default baud rate is 9600
    BTSerial.begin(9600);  
    Serial.println("BTserial started at 9600");
    
    //Initialize the DHT object
    dht.begin();
}
 
void loop()
{
  //Read temperature   
  temperature = dht.readTemperature();
  String tempString = String(temperature); //convert to string before sending it over serial
  
  //Read humidity
  humidity = dht.readHumidity();
  String humString = String(humidity); //convert to string before sending it over serial
  
  //Reading from the DHT11 takes ~250 ms
  delay(250);
  
  //Display temperature and humidity in the serial monitor
  //Used for debugging
 /* Serial.print(temperature);
  Serial.print(";");
  Serial.print(humidity);
  Serial.print("\n"); */
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  } 
  
  //MANUAL INPUT AND COMMAND MIRRORING/////////////////////////
  // Keep reading from HC-06 and send to Arduino Serial Monitor
  if (BTSerial.available())
    Serial.write(BTSerial.read());
 
  // Keep reading from Arduino Serial Monitor and send to HC-06
  if (Serial.available())
  BTSerial.write(Serial.read());
  /////////////////////////////////////////////////////////////
  
  //Sending sensor readings to the HC-05 master
  if (BTSerial.available()){
    String connectionConfirmation = BTSerial.readString();
    Serial.print(connectionConfirmation); //for debugging
    
    //Wait for the master to send its pairing confirmation message,
    //then format and send sensor readings.
    if(connectionConfirmation = "P"){
      Serial.print(tempString+humString);
      BTSerial.print(tempString + ";" + humString);
    }
  }
}
