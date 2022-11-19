#include <LiquidCrystal.h>
LiquidCrystal lcd(3, 2, 4, 5, 6, 7);

#define sensor 10
#define start 10
int p=0;
int delay1()
{ 
  float time1=millis();
 
  //unsigned int long k;
    int i,j;
    unsigned int count=0;
    for(i=0;i<1000;i++) 
    {
      for(j=0;j<1227;j++)
      {
       if(digitalRead(sensor))
       {
         count++;
         while(digitalRead(sensor)){
          if((millis()-time1)==5000){
              return count;
         }
       }
    }
  }
//  Serial.println(millis()-time1);
//    return count;
}}

void setup() 
{
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(start, INPUT);
  pinMode(13, OUTPUT);
  lcd.begin(16, 2);
  Serial.println("Techometer");
  lcd.setCursor(0,1);
  Serial.println("Circuit Digest");
  digitalWrite(start, HIGH);
}


void loop() 
{
     unsigned int time=0,RPM=0;
  
     Serial.println("Reading RPM.....");
     time=delay1();
  
     Serial.println("Please Wait.....");
     RPM=(time*12)/3;
 
     Serial.println("RPM=");
     Serial.println(RPM);
     delay(500);
     
}
