#include <Wire.h>
#include <RTClib.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 49
#define SS_PIN 53

RTC_DS3231 rtc;
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); // Program derlendiği zamanı ayarlar
  }

  SPI.begin();
  rfid.PCD_Init();
}

String getFormattedDateTime() {
  DateTime now = rtc.now();
  char buffer[11];
  sprintf(buffer, "%02d%02d%02d%02d%02d", 
          now.day(), now.month(), now.year() % 100,
          now.hour(), now.minute());
  return String(buffer);  // Örnek: "1501251359"
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;


  String timeStr = getFormattedDateTime();
  Serial.println(timeStr);

  byte block = 1;
  byte dataToWrite[16];
  memset(dataToWrite, 0, sizeof(dataToWrite));
  memcpy(dataToWrite, timeStr.c_str(), timeStr.length());

  MFRC522::StatusCode status;

  // Önce blok temizle
  byte emptyBlock[16] = {0};
  status = rfid.MIFARE_Write(block, emptyBlock, 16);

  delay(50); // Yazma öncesi kısa gecikme

  // Yeni veriyi yaz
  status = rfid.MIFARE_Write(block, dataToWrite, 16);
 

  rfid.PICC_HaltA(); // Kartı pasif hale getir
  rfid.PCD_StopCrypto1(); // Şifrelemeyi durdur
  delay(2000);
}
