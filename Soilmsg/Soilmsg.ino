
/*

*   Developed by Nilesh Patil on 27 March 16

*   WARNING: When uploading a code ==> Power-off Relays

*/

void setup()
{
  Serial.begin(115200);         // Setting the baudrate at 9600
  pinMode(A0, INPUT); //set up analog pin 0 to be input
    pinMode(8, OUTPUT);
}

void loop()
{
  int s = analogRead(A0); //take a sample
  //Serial.print(s);
  
  if(s < 1000 && s >= 500)
{ 
  digitalWrite(8, HIGH);
  Serial.print("AT+CMGF=1\r\n");
  delay(5000);
  Serial.print("AT+CMGS=\"");
  Serial.print("810000000000");//User Mobile No.
  Serial.print("\"\r\n");
  delay(2000);
  Serial.print("Motor is On");
  Serial.write(0x1A);
  while(1);
}


  if(s < 500) 
  {
   digitalWrite(8, LOW);
  Serial.print("AT+CMGF=1\r\n");
  delay(5000);
  Serial.print("AT+CMGS=\"");
  Serial.print("810000000000");//User Mobile No.
  Serial.print("\"\r\n");
  delay(2000);
  Serial.print("Motor is Off");
  Serial.write(0x1A);
  while(1); 
}
}
