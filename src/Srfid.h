#ifndef SRFID_h
#define SRFID_h

#include <MFRC522.h>
#include <Arduino.h>

class Srfid {

  private: 
    MFRC522 *rfid;
    MFRC522::Uid *uid;
    MFRC522::MIFARE_Key *key;

    bool authenticate(byte trailerBlock);

  public:
    Srfid(MFRC522 *rfid, MFRC522::MIFARE_Key *key);

    void init();

    void verify();

    void finaly();

    void setName(byte *buffer);

    void setLastName(byte *buffer);

    String getType();

    String getUUID();

    String getBase(byte sector, byte blockAddr, byte trailerBlock);

    String getName();

    String getLastName();

    String getFullName(String separator);
    
    void resetKey();
};

#endif