import processing.serial.*;

Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port
String address;
String temp;
String hum;
String readings [];

void setup()
{
  // I know that the first port in the serial list on my mac
  // is Serial.list()[0].
  // On Windows machines, this generally opens COM1.
  // Open whatever port is the one you're using.
  size(600,600);
  background(255,255,255);
  String portName = Serial.list()[1]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
}

void draw()
{
  if( myPort.available() > 0) 
  {  // If data is available,
  val = myPort.readStringUntil('\n');         // read it and store it in val
  }
  if(val!=null && val.length() > 10){
  //print(val); //print it out in the console
  //address=val.substring(1,10);
  //temp=val.substring(12,17);
  //hum=val.substring(19,23);
  readings = split(val,';');
  for(int i = 0; i < readings.length; i++){
   println(readings[i]);
   //text(readings[i], 50, 30*i);
  }
  
 // address = readings[0].substring(readings[0].length()-10,readings[0].length());
 // println("Address: " + address);
  //temp = readings[1].substring(1,5);
  //println("Temperature: " + temp + " degC");
  //hum = readings[2];
  //println("Humidity: " + hum + "%");
  text(readings[2],100,100);
  
 }
}
