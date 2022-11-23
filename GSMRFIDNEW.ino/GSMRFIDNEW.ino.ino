#include <SoftwareSerial.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
SoftwareSerial sim(4, 5);// Rx,TX; 
int rst = 9;
int ss =10;
int p=0;
int pos=0;
String TexT ="";
String number = "+919116207724 ";
MFRC522 rf(ss , rst);
Adafruit_SSD1306 display(-1);
Servo s1 ;
//.........................................
void setup(){
Serial.begin(9600);
sim.begin(9600); 
sim.println("AT+CMGF=1");
delay(500);
updatesim();
sim.println("AT+CNMI=2,2,0,0,0");
delay(1000);
updatesim();
SPI.begin();
rf.PCD_Init();
Serial.println("HI SIR \n ACTIVATED");
display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
TexT ="     Warmachine\n advanced security \n  system";
screen();
s1.attach(3);
s1.write(pos);
delay(100);
s1.write(120);
delay(1000);
s1.write(pos);
delay(3000);
}
//....................
void loop() 
{
  TexT ="\n       NO CARD";
screen();
  if(!rf.PICC_IsNewCardPresent())
  {
   return;
  }
if(!rf.PICC_ReadCardSerial())
{
  return;
}
String tag="";
rf.PCD_StopCrypto1();
for( int i=0; i<rf.uid.size; i++)
{
  tag.concat(String(rf.uid.uidByte[i],HEX));//card F4D3362A ..tag 97627A7A
}
tag.toUpperCase();
Serial.println(tag);

if ( tag == "F4D3362A")  

{ 
  TexT = "\n    Welcome Sir" ;
  screen();
  Serial.println("welcome sir");
  s1.write(180);
  delay(3000);
  s1.write(pos);
  delay(50);
}
else {
  Serial.println("not allowed");
  p=p+1;
  Serial.print("attempet left = ");
  Serial.print(6-p);
  Serial.println("/5");
  delay(100);
  display.clearDisplay();
  display.setCursor(0,0);
   display.setTextSize(1);
   display.setTextColor(WHITE);//"   ! ALERT! \n Hi sir ome wants to enter in room \n "
    display.print("  NOT ALLOWED  \n\n Attempts left = ");
       display.println(6-p);
     display. display();
     delay(900);
}
if(p==6)
{
  p=0;
   Serial.println("SYSTEM BLOCKED ");
  TexT = "       Varifing to\n\n  Mr. Suryansh";
  screen();
  SendMessage();
while (true)
{
  String sms="";
    if(!rf.PICC_IsNewCardPresent())
  {
  }
if(!rf.PICC_ReadCardSerial())
{
}
String tag1="";
for( int i=0; i<rf.uid.size; i++)
{
  tag1.concat(String(rf.uid.uidByte[i],HEX));//card F4D3362A ..tag 97627A7A
}
tag1.toUpperCase();
Serial.println("hii");
 if(tag1 == "F4D3362A")
 {
   TexT ="\n\  you are welcome";
   screen();
   s1.write(180);
   delay(3000);
   s1.write(pos);
   tag1="";
   break;
 }
  else
  {
    if(Serial.available()>0)
    {
      sms = Serial.readString();
     sms.trim();
     sms.toUpperCase();
     if(sms.indexOf("SURYA.OPEN")>=0)
     {
     TexT ="\n  you are welcome";
     screen();
     s1.write(180);
   delay(3000);
   s1.write(0);
   break;
   }
  
   else 
   {
    if(sms.indexOf("SURYA.RESET")>=0)
   {
   TexT ="\n System reset try    again";
   screen();
   delay(2000);
   break; 
    }
   }}
  }
 }
}
}
//.........................
void screen()
{ 
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);//"   ! ALERT! \n Hi sir ome wants to enter in room \n "
  display.println(TexT);
  display. display();   
}
void SendMessage()
{
  sim.println("AT+CNMI=2,2,0,0,0");
  delay(500);
  sim.println("AT+CMGF=1");
  delay(500);
  sim.println("AT+CMGS=\"+919116207724\"\r");
  delay(500);
  delay(500);
  sim.print("   ! ALERT! \n Hi sir someone  wants to enter in security place..\n WHAT TO DO ?");
  delay(500);
  sim.write(26);
}
void updatesim()
{
  if(sim.available()>0)
  {
  Serial.write(sim.read());
  delay(400);
  }
}
