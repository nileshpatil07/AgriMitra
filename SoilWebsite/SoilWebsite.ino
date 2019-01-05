/*

*   Developed by Nilesh Patil on 27 March 16

*   WARNING: When uploading a code ==> Power-off Relays

*/


#include <SoftwareSerial.h>         // including the library for the software serial
#define DEBUG true
SoftwareSerial esp8266(10,11);      /* This will make the pin 10 of arduino as RX pin and
pin 11 of arduino as the TX pin Which means that you have to connect the TX from the esp8266
to the pin 10 of arduino and the Rx from the esp to the pin 11 of the arduino*/
                                   

void setup()
{
  Serial.begin(115200);         // Setting the baudrate at 9600
  esp8266.begin(115200);        // Set the baudrate according to you esp's baudrate. your esp's baudrate might be different from mine
    pinMode(A0, INPUT); //set up analog pin 0 to be input
    pinMode(13, OUTPUT);
  
  sendData("AT+RST\r\n",2000,DEBUG);            // command to reset the module
  sendData("AT+CWMODE=3\r\n",1000,DEBUG);       // This will configure the mode as access point
  sendData("AT+CIFSR\r\n",1000,DEBUG);          // This command will get the ip address
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG);       // This will configure the esp for multiple connections
  sendData("AT+CIPSERVER=1,8080\r\n",1000,DEBUG); // This command will turn on the server on port 80
}

void loop()
{
  int s = analogRead(A0); //take a sample
  //Serial.print(s); 
 
  
    
  if(esp8266.available())         // This command will that check if the esp is sending a message 
  {    
    if(esp8266.find("+IPD,"))
    {
     delay(1000);
     int connectionId = esp8266.read()-48; /* We are subtracting 48 from the output because the read() function returns 
                                            the ASCII decimal value and the first decimal number which is 0 starts at 48*/
     String webpage;
      //webpage +="<html>";
     webpage += "<center>"; 
      webpage +=  "<body bgcolor=#98FB98>";
     webpage +="<div align=\"top\" style=\"width:1024;height:100;border:solid;border-width:10;\"><h1>AgriMitra</h1>";
       webpage += "<p><h2>";   
       if(s >= 1000) {
   webpage += "<div style=\"background-color:YellowGreen; width:600;height:200;border:solid;border-width:5;\"><h2>Sensor is not in the Soil or DISCONNECTED</h2>";
  }
  if(s < 1000 && s >= 600) 
  { 
  webpage += "<div style=\"background-color:YellowGreen; width:600;height:200;border:solid;border-width:5;\"><h2>Soil is DRY</h2>"; 
  }
  if(s < 370) 
  {
   webpage += "<div style=\"background-color:YellowGreen; width:600;height:200;border:solid;border-width:5;\"><h2>Sensor is in WATER</h2>";
   
   }
  delay(1000);
           
          webpage += "</center>"; 
          webpage +="<marquee>Copyright:Ptes</marquee>";
       webpage += "</h2></p></body>";
       

      //  webpage +=
     String cipSend = "AT+CIPSEND=";
     cipSend += connectionId;
     cipSend += ",";
     cipSend +=webpage.length();
     cipSend +="\r\n";

     sendData(cipSend,1000,DEBUG);
     sendData(webpage,1000,DEBUG);    
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; 
     closeCommand+="\r\n";
     sendData(closeCommand,3000,DEBUG);
    }
  }
}
 
String sendData(String command, const int timeout, boolean debug)
{
    String response = "";   
    esp8266.print(command); 
    long int time = millis();
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
        char c = esp8266.read(); 
        response+=c;
      }  
    }
    if(debug)
    {
      Serial.print(response);
    }
    return response;
}

