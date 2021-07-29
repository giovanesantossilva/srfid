# Srfid

> Simple arduino library for rfid RC522

## Table of contents

- [Main](#main)
- [Getting started](#getting-started)
- [Methods](#methods)
- [License](#license)

## Main

```text
src/
├── Srfid.cpp       
└── Srfid.h
```

## Getting started

### Basic use
```cpp
#include <SPI.h> // Dependencies
#include <MFRC522.h> // Dependencies

#include <Srfid.h> // Library Srfid

#define PIN_SS 4
#define PIN_RESET 5

MFRC522::MIFARE_Key key;
MFRC522 rfid(PIN_SS, PIN_RESET);

Srfid myRfid(&rfid, &key);
```

## Methods

### Srfid::Srfid(MFRC522 *rfid, MFRC522::MIFARE_Key *key)

Constructor of Srfid

- *rfid: Pointer to MFRC522 instace
- *key: Pointer to MIFARE_Key definition

```cpp
Srfid myRfid(&rfid, &key);
```

### void Srfid::init()

Init SRFID card

````cpp
myRfid.init();
````

### void Srfid::resetKey()

Clear Srfid key default

````cpp
myRfid.resetKey();
````

### void Srfid::verify()

Check if the card is present and valid

````cpp
myRfid.verify();
````

### void Srfid::finaly()

Closes all operations

````cpp
myRfid.finaly();
````

### String Srfid::getType()

Get type of card rfid

````cpp
Serial.print("Type: ");
String type = myRfid.getType(); 
Serial.println(type);
````

### String Srfid::getUUID()

Get uid of card rfid

````cpp
Serial.print("UID: ");
String uid = myRfid.getUUID(); 
Serial.println(uid);
````

### String Srfid::getName()

Get name of card rfid, sector 1, blockAddr 4, trailerBlock 7

````cpp
Serial.print("Name: ");
String name = myRfid.getName(); 
Serial.println(name);
````

### String Srfid::getLastName()

Get last name of card rfid, sector 0, blockAddr 1, trailerBlock 3

````cpp
Serial.print("Last Name: ");
String lastName = myRfid.getLastName(); 
Serial.println(lastName);
````

### String Srfid::getFullName(String separator)

Get full name of card rfid 

- separator: separator between strings

````cpp
Serial.print("FullName: ");
String fullname = myRfid.getFullName(" ");
Serial.println(fullname);
````

### void Srfid::setName(byte *buffer)

Set name in the card if valid authenticate

- *buffer: string with content

````cpp
byte buffer[34], len;
Serial.setTimeout(20000L); 
Serial.println(F("Enter the name, then the character #"));
len = Serial.readBytesUntil('#', (char *) buffer, 30);
for (byte i = len; i < 30; i++) buffer[i] = ' ';

srfid.setName(buffer);
````

### void Srfid::setLastName(byte *buffer)

Set name in the card if valid authenticate

- *buffer: string with content

````cpp
byte buffer[34], len;
Serial.setTimeout(20000L); 
Serial.println(F("Enter the name, then the character #"));
len = Serial.readBytesUntil('#', (char *) buffer, 30);
for (byte i = len; i < 30; i++) buffer[i] = ' ';

srfid.setLastName(buffer);
````

## License

[MIT](https://opensource.org/licenses/MIT) © [Giovane Santos](https://giovanesantossilva.github.io/)