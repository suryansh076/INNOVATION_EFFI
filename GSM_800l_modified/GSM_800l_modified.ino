#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>
#define OLED_RESET 4
Adafruit_SH1106 display(OLED_RESET);
SoftwareSerial mySerial(4, 5);
void setup()
{

  Serial.begin(9600);
  mySerial.begin(9600);
  display.begin(SH1106_SWITCHCAPVCC, 0x3C);
  Serial.println("Initializing2...");
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println("AT+CNMI=2,2,0,0,0");
  updateSerial();
  delay(1000);
  //  display.clearDisplay();
  //  display.setCursor(0, 0);
  //  display.setTextSize(1);
  //  display.setTextColor(WHITE);//"   ! ALERT! \n Hi sir ome wants to enter in room \n "
  //  display.print("Dual axis solar, Digital Notice board");
  //  display. display();
  //  delay(2000);

}

void loop()
{
  updateSerial();

}

void updateSerial()
{
  String s = "";
  while (mySerial.available() > 1)
  {
    //    delay(1000);
    s = mySerial.readString();
    s.trim();
    if (s.length() > 1)
    {
      if (s.indexOf("+CMT:") >= 0)
      {
        s.remove(0, 47);
      }
      Serial.print(s);
    }
    //    display.clearDisplay();
    //    display.setCursor(0, 0);
    //    display.setTextSize(1);
    //    display.setTextColor(WHITE);
    //    display.print(s);
    //    display. display();

  }
}
