# RFID-DS3231: RFID Kartına Tarih ve Saat Kaydedici

Bu proje, bir Arduino kartı, bir **DS3231 Gerçek Zaman Saati (RTC)** modülü ve bir **MFRC522 RFID okuyucu** kullanarak, algılanan bir RFID kartına anlık tarih ve saat bilgisini yazar. Proje, özellikle RFID kartlarına zaman damgası basma veya temel veri depolama gibi uygulamalar için idealdir.

## Proje Yapısı ve Donanım
Bu projenin temel bileşenleri şunlardır:

* **Arduino Kartı**: Kodun çalıştırıldığı ana mikrodenetleyici.
* **MFRC522 RFID Okuyucu Modülü**: RFID kartlarını algılamak ve üzerlerine veri yazmak için kullanılır.
* **DS3231 RTC Modülü**: Hassas ve pil destekli bir gerçek zaman saati modülüdür. Bu sayede Arduino'nun güç kaynağı kesilse bile doğru zaman bilgisi korunur.
* **RFID Kartı/Etiketi**: Üzerine verinin yazılacağı Mifare tabanlı kart.

### Bağlantı Şeması

Bağlantıları doğru yapmak için aşağıdaki pin tanımlamalarını kullanabilirsiniz:

**MFRC522 RFID Okuyucu Bağlantıları:**
* **RST_PIN**: Arduino'da `49` numaralı pine bağlıdır.
* **SS_PIN**: Arduino'da `53` numaralı pine bağlıdır.
* **Diğer SPI Pinleri**: MFRC522 modülünün SCK, MISO, MOSI pinleri Arduino'nun SPI portuna (genellikle 50, 51, 52) bağlanır.

**DS3231 RTC Bağlantıları:**
* **SDA**: Arduino'nun SDA pinine bağlanır (Uno için A4, Mega için 20).
* **SCL**: Arduino'nun SCL pinine bağlanır (Uno için A5, Mega için 21).

## Kullanılan Kütüphaneler

Projenin çalışabilmesi için Arduino IDE'ye aşağıdaki kütüphanelerin eklenmesi gerekmektedir:

* **Wire.h**: I2C iletişimi için.
* **RTClib.h**: DS3231 RTC modülü ile iletişim için.
* **SPI.h**: RFID modülü ile SPI iletişimi için.
* **MFRC522.h**: RFID modülü için özel komutları içerir.

Bu kütüphaneleri Arduino IDE'nin Kütüphane Yöneticisi'nden kolayca aratıp yükleyebilirsiniz.




