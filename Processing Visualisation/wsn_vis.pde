/*
*@author Tsonyo Vasilev
*@version 0.1
*
*This script displays a basic visualization of the current readings
*from each of the remote nodes of the wireless sensor network.
*/
import processing.serial.*;

Serial myPort;  // Create object from Serial class
String val;     // Data received from the serial port
String address;
String temp;
String hum;
//Store the input string once split
String readings [];
//Aux variable for drawing the temperature bar
int yDist;

void setup()
{
  size(600,600);
  background(50);
  String portName = Serial.list()[1];
  myPort = new Serial(this, portName, 9600);
}

void draw()
{
  fill(255);
  if( myPort.available() > 0) 
  {  // If data is available,
    val = myPort.readStringUntil('\n');         // read it and store it in val
  }
  
  //Wait till the value on the serial port is of sufficient length
  if(val!=null && val.length() > 10){
    readings = split(val,';');
    for(int i = 0; i < readings.length; i++){
    println(readings[i]);
  }
  
  //Draw output on different parts of the canvas
  //depending on which sensor is read
  if(readings[0].trim().equals("14,3,5593E")){
    fill(50);
    noStroke();
    rect(50,50,300,200);
    textSize(20);
    fill(120);
    text("Remote Node 1", 50, 50);
    fill(140);
    text("Address: " + readings[0], 50,80);
    text("Temperature: " + readings[1].substring(1,readings[1].length()-1)+ " degC", 50,100);
    text("Relative humidity: "+readings[2], 50,120);
    fill(90);
    text("Latest reading: " + str(hour())+":"+str(minute())+":"+str(second()),50,140);
  }else if(readings[0].trim().equals("14,3,5597A")){ 
    fill(50);
    noStroke();
    rect(50,300,300,200);
    textSize(20);
    fill(120);
    text("Remote Node 2", 50, 300);
    fill(140);
    text("Address: " + readings[0], 50,330);
    text("Temperature: " + readings[1].substring(1,readings[1].length()-1)+ " degC", 50,350);
    text("Relative humidity: "+readings[2], 50,370);
    fill(90);
    text("Latest reading: " + str(hour())+":"+str(minute())+":"+str(second()),50,390);
  }
  
   /*
   //draw the temp rectangle
   
    colorMode(RGB, 160);  //use color mode sized for fading
    stroke (0);
    rect (49,19,22,162);
    //fade red and blue within the rectangle
    for (int colorIndex = 0; colorIndex <= 160; colorIndex++) 
    {
      stroke(160 - colorIndex, 0, colorIndex);
      line(50, colorIndex + 20, 70, colorIndex + 20);
    }
    int temperature = int(readings[1].substring(1,readings[1].length()-1));
    //draw triangle pointer
    yDist = int(160 - (160 * (temperature * 0.01)));
    stroke(0);
    triangle(75, yDist + 20, 85, yDist + 15, 85, yDist + 25);
    */
 }
}
