#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

#include <SoftwareSerial.h>
#define rxPin 7
#define txPin 7

SoftwareSerial MySerial = SoftwareSerial(rxPin,txPin);
String imprimi = "";

void setup() 
{
  Serial.begin(9600);   // Inicia a serial
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  digitalWrite(txPin,HIGH);
  pinMode(txPin,OUTPUT);
  MySerial.begin(9600);
}

void LCD_CMD(int Command){
  MySerial.write(0xFE); // Command
  MySerial.write(Command);
}
 
void loop() 
{
  char caractere;
  // Enquanto receber algo pela serial
  while(Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n'){
      // Concatena valores
      imprimi.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }
  
    if(imprimi !=  ""){
      LCD_CMD(0x80); // First Line
      MySerial.print("Seja bem Vindo!");
  
      LCD_CMD(0xC0); // Second Line
      MySerial.print(imprimi);
      delay(3000);
      imprimi = "";
      LCD_CMD(0x01); // Clear Screen Command
    }
    
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  
  delay(500);
 
} 

