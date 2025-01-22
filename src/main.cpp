#include <SPI.h>                  // Include SPI library for RFID communication
#include <MFRC522.h>              // Include MFRC522 library for RFID
#include <Wire.h>                 // Include Wire library for I2C communication

// RFID pins
#define SS_PIN 5                 // Define Slave Select pin for RFID
#define RST_PIN 2                 // Define Reset pin for RFID

MFRC522 rfid(SS_PIN, RST_PIN);    



void setup() {
  Serial.begin(9600);             // Start serial communication at 9600 baud rate

  // Initialize RFID
  SPI.begin();                    // Initiate SPI bus
  rfid.PCD_Init();                // Initiate MFRC522 RFID module


  delay(2000);                    // Wait for 2 seconds
}

void loop() {
  // Look for new cards
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;                       // If no new card is present, exit the loop
  }

  // Display UID on Serial Monitor
  Serial.print("UID tag: ");
  String content = "";            // Create a string to hold the UID content
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX); // Print each byte of the UID in HEX format
    content.concat(String(rfid.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(rfid.uid.uidByte[i], HEX)); // Append each byte to the content string
  }
  Serial.println();
  Serial.println();


  delay(2000);                    // Hold the display for 2 seconds

  // Halt PICC
  rfid.PICC_HaltA();              // Halt the PICC (card)
}
