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

## Nasıl Kullanılır?

1.  Yukarıdaki donanımları ve bağlantıları doğru bir şekilde yapın.
2.  Gereken kütüphaneleri Arduino IDE'ye ekleyin.
3.  Sağlanan kodu kopyalayıp Arduino IDE'ye yapıştırın.
4.  Kodu derleyin ve Arduino kartınıza yükleyin.
5.  Seri Monitörü açın (9600 baud hızında).
6.  Bir RFID kartını MFRC522 okuyucusuna yaklaştırın.
7.  Kartın ID'si okunduğunda, seri monitörde kartın üzerine yazılan tarih ve saat bilgisini göreceksiniz. Her yeni kart okutulduğunda, kart üzerindeki veri güncellenecektir.

## Kod Açıklaması

* `setup()` fonksiyonu içinde, Seri Port, I2C ve SPI haberleşmeleri başlatılır. `rtc.lostPower()` kontrolü ile eğer RTC modülü güç kaybetmişse, programın derlenme zamanını kullanarak saat ayarı yapılır.
* `getFormattedDateTime()` fonksiyonu, DS3231'den okunan tarih ve saat bilgisini `DDMMYYHHmm` formatında (örneğin: `1501251359`) bir string olarak döndürür.
* `loop()` fonksiyonu, sürekli olarak yeni bir RFID kartının yaklaştırılıp yaklaştırılmadığını kontrol eder.
* Eğer yeni bir kart algılanırsa, `getFormattedDateTime()` fonksiyonundan alınan zaman stringi `dataToWrite` adlı bir byte dizisine kopyalanır.
* Daha sonra `MIFARE_Write()` fonksiyonu kullanılarak RFID kartının ilgili bloğuna (bu örnekte `blok 1`) önce boş veri yazılıp temizlenir, ardından yeni zaman verisi yazılır.
* Son olarak, kart pasif hale getirilir ve yeni bir okuma için kısa bir bekleme süresi verilir.

## Lisans

Bu proje MIT Lisansı ile lisanslanmıştır. Daha fazla bilgi için `LICENSE` dosyasına göz atabilirsiniz.
