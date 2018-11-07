
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
int led = 0;

char auth[] = "token";              // kendi tokeninizi girin

char ssid[] = "wifiadi";            // Wifi ağının adı
char pass[] = "wifisifresi";        // Wifi ağının şifresi

#define DHTPIN 4                    // Dht11'in sinyal bacağının bağlandığı pin 


#define DHTTYPE DHT11               // DHT 11 - Kullanılan DHT tipi
//#define DHTTYPE DHT22             // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21             // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t); 


/*************************************** - LED bağlanırsa aktif yapılacak kısım
 
  if ( t >= 28)                       // Sıcaklık 28 dereceye ulaşırsa ya da geçerse
  {
    digitalWrite (led , HIGH);        // Ledi Yak
  }
  else 
  {
    digitalWrite (led , LOW);          // Aksi halde Ledi Söndür
  }
  
***************************************/
}

void setup()
{
  Serial.begin(9600);
  pinMode (led, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
}


void loop()
{
  Blynk.run();
  timer.run();
}

