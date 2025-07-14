//Defining pins and necessary inclyde statements 

/*RFID READER*/
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

#define RST_PIN 8 //Pin 8 will be connected reset pin
#define SS_PIN  9 //pin 9 will be connected to SDA


// Step 1: Initialize RFID and Servo

/*Creating Instance*/
MFRC522 RFID(SS_PIN, RST_PIN);
Servo servo;


void setup(){

  Serial.begin(9600); //Initialize serial communications with the PC
  SPI.begin(); // Initialize MFRC522
  RFID.PCD_Init();//initialize the MFRC522
  servo.attach(7); //attach servo to pin 7
  

  Serial.println(F("Scan the card Please"));


}
// Step 2: Wait for a card

/*If Statement Needed in loop*/

void loop(){

if(! RFID.PICC_IsNewCardPresent()){
  return;
  }

// Step 3: Read UID
if(! RFID.PICC_ReadCardSerial()){

  return;
  }

// Step 4: Check if UID matches authorized card
boolean authorizedCard = true;
//this is the correct uid we are trying to match
byte authorizedUID[] {0xB4, 0x87, 0x0C, 0x06};

//check by using a for loop
for(byte i = 0; i < RFID.uid.size; i++){
  if(RFID.uid.uidByte[i] != authorizedUID[i]){

      authorizedCard = false;

      break;

    }

  }

// Step 5: If yes, unlock with servo

if(authorizedCard){

  for(int position = 0; position <=180; position++){

      servo.write(position);
      delay(15);
  }

}

// Step 6: Wait, then lock again

delay(5000);


for(int position = 180; position >= 0; position--){


  servo.write(position);
  delay(15);
  }
}

