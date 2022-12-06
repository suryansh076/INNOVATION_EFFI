#include<Dictionary.h>
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
int relay = 5;
MFRC522 mfrc522(SS_PIN, RST_PIN);
//Dictionary<String, String> My_Dict;
String book_taker;
String curr_user;
int bookid1 = 2;
bool bookpre = true;
int timee=0;
int timercount = 0;
String s[][20] = {{"A3 99 1F 0A", "Mohit"}, {"14 AB 1C 2B", "Shashank"}};
int si = 0;
void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
//  My_Dict.set("14AB1C2B", "ANALOG");
//  My_Dict.set("A3991FA", "DSA");

  si = sizeof(s) / sizeof(s[0]);
  //Serial.println(si);

  //  Serial.print(" UID tag :");
  pinMode(relay, OUTPUT);
  pinMode(bookid1, INPUT);
  digitalWrite(relay, 0);
}
void loop() {
  if (!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial())
  {
    return;
  }
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  content.toUpperCase();
  Serial.print(digitalRead(bookid1));
  //  Serial.println(content.substring(1));
  Serial.println();
  for ( int i = 0; i < si; i++)
  {
    if ( content.substring(1) == s[i][0])
    {

      Serial.println("Hello  " + s[i][1]);
      timercount = 1;
      curr_user = s[i][1];
      openbookid1();
    }
  }
  if (timercount == 1)
  {
  
//      timee = millis();
//      while ((millis() - timee) < 5000)
//    {

      if (bookpre && digitalRead(bookid1) == 0)
      {
        bookpre = !bookpre;
        Serial.println();
        Serial.print("Book issue to  ");
        Serial.println(curr_user);
        book_taker = content.substring(1);
      }
      if (digitalRead(bookid1) == 1 && !bookpre)
      {
        if (content.substring(1) == book_taker)
        {
           bookpre = !bookpre;
           book_taker="";
          Serial.println(curr_user + " returnd the book");
        }
        else {
          Serial.println("book is already issued to some other student dont put any book in this slot");
//          break;
        }
      }

//    }
//    timee=millis();
  }
  else
  {
    Serial.println("byeee");
  }
  Serial.println(bookpre);
  Serial.println(book_taker);
  delay(500);
  timercount=0;
  content.substring(1)="";
}
  void openbookid1()
  {
    Serial.println("Door Unlocked");
    digitalWrite(relay, 1);
    delay(5000);
    Serial.println("Door Locked");
    digitalWrite(relay, 0);
  }
