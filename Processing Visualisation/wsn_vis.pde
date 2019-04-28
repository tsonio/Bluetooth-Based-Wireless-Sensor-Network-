/*
*@author Tsonyo Vasilev
*@version 0.3
*
*version 0.3: GUI updated to show data for three sensors, added
*a message to be displayed when the network is active at the bottom.
*
*version 0.2: Added temperature bar graphs. New data is now
*indicated by a green dot next to the name of the slave.
*
*This script displays a basic visualisation of the current readings
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

void setup()
{
  size(350,830);
  background(50);
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
}

void draw()
{
    
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
  
    //Reset first new data circle
    noStroke();
    fill(50);
    ellipse(25, 45, 30,30);
    
    //Reset second new data circle
    noStroke();
    fill(50);
    ellipse(25, 295, 30,30);
    
    //Reset third new data circle
    noStroke();
    fill(50);
    ellipse(25, 545, 30,30);
    
    //Clear standby message
    noStroke();
    fill(50);
    rect(50,720,350,250);
    
    
    
  //Draw output on different parts of the canvas
  //depending on which sensor is read
  if(readings[0].trim().equals("14,3,5593E")){
    //Reset data display
    fill(50);
    noStroke();
    rect(50,50,300,200);
    
    //Reset temperature bar
    noStroke();
    fill(50);
    rect(40, 155, 260, 40);
    
    textSize(20);
    fill(120);
    text("Remote Node 1", 50, 50);
    fill(140);
    text("Address: " + readings[0], 50,80);
    text("Temperature: " + readings[1].substring(1,readings[1].length()-1)+ " degC", 50,100);
    text("Relative humidity: "+readings[2], 50,120);
    fill(90);
    text("Latest reading: " + str(hour())+":"+str(minute())+":"+str(second()),50,140);
    //New data indicator
    fill(0,255,0);
    noStroke();
    ellipse(25, 45, 20,20);
    
    //Temperature bar graph
    float temp = parseFloat(readings[1].substring(1,readings[1].length()-1)); //Get temperature as float
    //Draw background
    noStroke();
    fill(90);
    rect(45, 160, 250, 30);
    //Draw temperature bar
    int tempRange = 40;
    int barSize= (240/tempRange)*parseInt(temp);
    fill(255,0,0);
    rect(50, 165, barSize, 20);
    //0°C mark
    fill(90);
    textSize(15);
    text("0°C", 45, 207);
    //40°C mark
    fill(90);
    textSize(15);
    text("40°C", 260, 207);
    
    //Clear standby message
    noStroke();
    fill(50);
    rect(50,720,350,250);
    
    //Network status text
    textSize(20);
    fill(0,255,0);
    text("SENSOR NETWORK ACTIVE",50,770);
    

  }else if(readings[0].trim().equals("14,3,5597A")){
    //Reset data display
    fill(50);
    noStroke();
    rect(50,300,300,200);
    
    //Reset temperature bar
    noStroke();
    fill(50);
    rect(45, 405, 260, 40);
    
    textSize(20);
    fill(120);
    text("Remote Node 2", 50, 300);
    fill(140);
    text("Address: " + readings[0], 50,330);
    text("Temperature: " + readings[1].substring(1,readings[1].length()-1)+ " degC", 50,350);
    text("Relative humidity: "+readings[2], 50,370);
    fill(90);
    text("Latest reading: " + str(hour())+":"+str(minute())+":"+str(second()),50,390);
    //New data indicator
    fill(0,255,0);
    noStroke();
    ellipse(25, 295, 20,20);
    
    //Temperature bar graph
    float temp = parseFloat(readings[1].substring(1,readings[1].length()-1)); //Get temperature as float
    //Draw background
    noStroke();
    fill(90);
    rect(45, 410, 250, 30);
    //Draw temperature bar
    int tempRange = 40;
    int barSize= (240/tempRange)*parseInt(temp);
    fill(255,0,0);
    rect(50, 415, barSize, 20);
    //0°C mark
    fill(90);
    textSize(15);
    text("0°C", 45, 457);
    //40°C mark
    fill(90);
    textSize(15);
    text("40°C", 260, 457);
    
    //Clear standby message
    noStroke();
    fill(50);
    rect(50,720,350,250);
    
    //Network status text
    textSize(20);
    fill(0,255,0);
    text("SENSOR NETWORK ACTIVE",50,770);
    
    
  }else if(readings[0].trim().equals("14,3,55917")){
    //Reset data display
    fill(50);
    noStroke();
    rect(50,550,300,200);
    
    //Reset temperature bar
    noStroke();
    fill(50);
    rect(45, 655, 260, 40);
    
    textSize(20);
    fill(120);
    text("Remote Node 3", 50, 550);
    fill(140);
    text("Address: " + readings[0], 50,580);
    text("Temperature: " + readings[1].substring(1,readings[1].length()-1)+ " degC", 50,600);
    text("Relative humidity: "+readings[2], 50,620);
    fill(90);
    text("Latest reading: " + str(hour())+":"+str(minute())+":"+str(second()),50,640);
    //New data indicator
    fill(0,255,0);
    noStroke();
    ellipse(25, 545, 20,20);
    
    //Temperature bar graph
    float temp = parseFloat(readings[1].substring(1,readings[1].length()-1)); //Get temperature as float
    //Draw background
    noStroke();
    fill(90);
    rect(45, 660, 250, 30);
    //Draw temperature bar
    int tempRange = 40;
    int barSize= (240/tempRange)*parseInt(temp);
    fill(255,0,0);
    rect(50, 665, barSize, 20);
    //0°C mark
    fill(90);
    textSize(15);
    text("0°C", 45, 707);
    //40°C mark
    fill(90);
    textSize(15);
    text("40°C", 260, 707);
    
    //Clear standby message
    noStroke();
    fill(50);
    rect(50,720,350,250);
    
    //Network status text
    textSize(20);
    fill(0,255,0);
    text("SENSOR NETWORK ACTIVE",50,770);
    
  }else if(readings[0].trim().equals("No response from slave, resetting...")){ //No response from slave, resetting...
    textSize(20);
    fill(90);
    text("NETWORK STANDING BY,\nPLEASE WAIT.",50,740);
  }
  
 }//end main "if"
}
