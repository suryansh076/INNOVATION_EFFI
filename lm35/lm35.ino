#include <SPI.h>
#include <LoRa.h>
float revolutions = 0;
int acc = 0;
int rpm = 0;
long timee;
int acce;
int temp;
int brake;
void interruptFunction();
void setup()
{
  pinMode(2, INPUT_PULLUP);
  pinMode(A0, INPUT);
  pinMode(A3, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(2), interruptFunction, RISING);
    while (!Serial);
    Serial.println("LoRa Sender");
  
    if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of your module
      Serial.println("Starting LoRa failed!");
      while (1);
    }
  timee = millis();

}
void loop() {
  if ((millis() - timee) >= 1000) {
    temp = 0;
    if (revolutions > 0)
    {
      rpm = (max(1, revolutions) * 60000) / 1000;      //calculates rpm
      temp = rpm;
    }
    //    Serial.print(rpm);
    //        Serial.print("   ");
    timee = millis();
    revolutions = 0;
    rpm = 0;
  }
//  Serial.println(temp);
  acce = analogRead(A0);
  delay(10);
  brake = analogRead(A3);
  delay(10);
  String all_data = String(temp) + ";" + String(acce) + ";" + String(brake);
//    Serial.print(acce);
//    Serial.print(" ");
//    Serial.println(brake);
    Serial.println(all_data);
    LoRa.beginPacket();
    LoRa.print(all_data);
    LoRa.endPacket();
    delay(100);
}

void interruptFunction()
{
  revolutions++;
}
