/**
 * @author Giovane Santos Silva
 */
#include <SPI.h>
#include <MFRC522.h>

#include <Srfid.h>

#define PIN_SS    4 // Configurable, see typical pin layout above
#define PIN_RESET 5 // Configurable, see typical pin layout above
 
MFRC522::MIFARE_Key key;
MFRC522 rfid(PIN_SS, PIN_RESET);

Srfid srfid(&rfid, &key);

void setup()
{
	Serial.begin(9600); // Initialize serial
	SPI.begin();        // Init SPI bus
	srfid.init();       // Init Srfid card
	srfid.resetKey();   // Clear Srfid key
}

void loop()
{
	srfid.verify(); // Check if the card is present and valid
	Serial.print("Type: ");
	String type = myRfid.getType(); // Get type of card rfid
	Serial.println(type);
	Serial.print("UUID: ");
	String uuid = myRfid.getUUID(); // Get uid  of card rfid
	Serial.println(uuid);
	Serial.print("Name: ");
	String nome = myRfid.getName(); // Get name of card rfid
	Serial.println(nome);
	Serial.print("Last: ");
	String last = myRfid.getLastName(); // Get last name of card rfid
	Serial.println(last);
	Serial.print("FullName: ");
	String fullname = myRfid.getFullName(" "); // Get full name with delimiter

	myRfid.finaly();
	delay(1000);
}