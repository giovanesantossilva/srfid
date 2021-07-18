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

	byte buffer[34], len;
	Serial.setTimeout(20000L); // Wait until 20 seconds for input from serial 
	Serial.println(F("Enter the name, then the character #"));
	len = Serial.readBytesUntil('#', (char *) buffer, 30); // Read family name from serial
	for (byte i = len; i < 30; i++) buffer[i] = ' '; // Pad with spaces

	srfid.setName(buffer); // Set name in the card if valid authenticate

	Serial.setTimeout(20000L) ;
	Serial.println(F("Enter the last name, then the character #"));
	len = Serial.readBytesUntil('#', (char *) buffer, 30) ;
	for (byte i = len; i < 30; i++) buffer[i] = ' ';

	srfid.setLastName(buffer); // Set last name in the card if valid authenticat

	srfid.finaly();
	delay(2000);
}