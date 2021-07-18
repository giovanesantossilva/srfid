#include <MFRC522.h>

#include "Srfid.h"

Srfid::Srfid(MFRC522 *rfid, MFRC522::MIFARE_Key *key) {
  this->rfid = rfid;
  this->key = key;
}

void Srfid::init() {
  Serial.println("[~SRFID] Init");
  this->rfid->PCD_Init();
  this->uid = &this->rfid->uid; 
}

void Srfid::resetKey() {
  Serial.println("[~SRFID] Reset key");
  for (byte i = 0; i < 6; i++) {
    this->key->keyByte[i] = 0xFF;
  }
}

void Srfid::verify() {
  Serial.println("[~SRFID] Verify...");
  while(!this->rfid->PICC_IsNewCardPresent()) {
    delay(100);
  }
  if(!this->rfid->PICC_ReadCardSerial()) return;
}

void Srfid::finaly() {
   this->rfid->PICC_HaltA(); 
   this->rfid->PCD_StopCrypto1();
}

bool Srfid::authenticate(byte trailerBlock) {
  MFRC522::StatusCode status = this->rfid->PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, this->key, this->uid);
  if(status != MFRC522::STATUS_OK) {
    #ifdef SRFID_ERROR_LOG
      Serial.print("[~SRFID] Authenticate failed: ");
    #endif
    Serial.println(this->rfid->GetStatusCodeName(status));
    return false;
  }
  return true;
}

void Srfid::setName(byte *buffer) {
  if(!this->authenticate(4)) return;
  MFRC522::StatusCode status = this->rfid->MIFARE_Write(4, buffer, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("[~SRFID] setName failed: ");
    Serial.println(this->rfid->GetStatusCodeName(status));
    return;
  }
  if(!this->authenticate(5)) return;
  status = this->rfid->MIFARE_Write(5, &buffer[16], 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("[~SRFID] setName failed: ");
    Serial.println(this->rfid->GetStatusCodeName(status));
    return;
  }
  Serial.println("[~SRFID] setName success: ");
}

void Srfid::setLastName(byte *buffer) {
  if(!this->authenticate(1)) return;
  MFRC522::StatusCode status = this->rfid->MIFARE_Write(1, buffer, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("[~SRFID] setLastName failed: ");
    Serial.println(this->rfid->GetStatusCodeName(status));
    return;
  }
  if(!this->authenticate(2)) return;
  status = this->rfid->MIFARE_Write(2, &buffer[16], 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("[~SRFID] setLastName failed: ");
    Serial.println(this->rfid->GetStatusCodeName(status));
    return;
  }
  Serial.println("[~SRFID] setLastName success: ");
}

String Srfid::getType() {
  MFRC522::PICC_Type piccType = this->rfid->PICC_GetType(this->uid->sak);
  return this->rfid->PICC_GetTypeName(piccType);  
}

String Srfid::getUUID() {
  String contents = "";
  for (byte i = 0; i < this->uid->size; i++) {
    contents.concat(String(this->uid->uidByte[i], HEX));
    if(i != (this->uid->size - 1)) {
      contents.concat(String(this->uid->uidByte[i] < 0x10 ? " 0" : ":"));
    }
  }
  return contents;
}

String Srfid::getBase(byte sector, byte blockAddr, byte trailerBlock) {
  byte buffer[18];
  byte size = sizeof(buffer);

  if(!this->authenticate(trailerBlock)) {
    return "";
  }
 
  MFRC522::StatusCode status = this->rfid->MIFARE_Read(blockAddr, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("[~SRFID] getBase failed: ");
    Serial.println(this->rfid->GetStatusCodeName(status));
    return "";
  }

  String contents = "";
  for (byte i = 1; i < 16; i++) {
    char caracter = buffer[i];
    if(!isWhitespace(caracter)) {
      contents.concat(caracter);
    }
  }
  return contents;
}

String Srfid::getName() {
  return this->getBase(1, 4, 7);
}

String Srfid::getLastName() {
  return this->getBase(0, 1, 3);
}

String Srfid::getFullName(String separator) {
  String fullname = "";
  fullname.concat(this->getName());
  fullname.concat(separator);
  fullname.concat(this->getLastName());
  return fullname;
}