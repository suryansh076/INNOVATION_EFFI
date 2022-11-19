#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(4,5); //SIM800L Tx & Rx is connected to Arduino #3 & #2

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);
  
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
//  mySerial.println("AT+CSQ"); //Signal quality test, value range is 0-31 , 31 is the best
//  updateSerial();
//  mySerial.println("AT+CCID"); //Read SIM information to confirm whether the SIM is plugged
//  updateSerial();
//  mySerial.println("AT+CREG?"); //Check whether it has registered in the network
//  updateSerial();
}

void loop()
{
  updateSerial();
}

void updateSerial()
{
  String s="";
  while(mySerial.available()>1){
  
//    delay(1000);
     s=mySerial.readString();
    s.trim();

  
  }
  if(s.length()>1)
  {
      if(s.indexOf("+CMT:")>=0)
      {
         s.remove(0, 47);
      }
      Serial.print(s);
  }
}
