#include <SPI.h> 
#include <MFRC522.h> 
#define SS_PIN 4 //D2 
#define RST_PIN 5 //D1 
MFRC522 mfrc522(SS_PIN, RST_PIN); 
void setup() { 
 Serial.begin(9600); 
 SPI.begin(); 
 mfrc522.PCD_Init(); 
} 
void loop(){ 
 if (!mfrc522.PICC_IsNewCardPresent()) 
 return; 
 if (!mfrc522.PICC_ReadCardSerial()) 
 return; 
 Serial.println(); 
 Serial.print(" UID tag :"); 
 String content = ""; 
 byte letter; 
 for (byte i = 0; i < mfrc522.uid.size; i++) 
 { 
 Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");  Serial.print(mfrc522.uid.uidByte[i], HEX); 
content.concat(String(mfrc522.uid.uidByte[i]<0x10?" 0":" "));  content.concat(String(mfrc522.uid.uidByte[i], HEX));  } 
 content.toUpperCase(); 
 Serial.println(); 
 if (content.substring(1) == "F4 4B F4 2A") { 
 Serial.println(" Access Granted \n Welcome Mr.Circuit");  delay(1000); 
 Serial.println(" Have FUN \n"); 
 } 
 else { 
 Serial.println(" Access Denied "); 
// delay(3000); 
 } 
}
