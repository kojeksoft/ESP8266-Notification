#include <ESP8266HTTPClient.h>
#include <ESP8266Wifi.h>

const char* ssid = "IniWifiSaya";
const char* password = "IniPasswordWifi";
const char* host = "8.219.209.62";

#define analogPin A0

int adcValue = 0;

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
delay(5000);
WiFi.hostname("NodeMCUBell");
WiFi.begin(ssid, password);
Serial.println("Wifi Connected");
}

void loop() {
  // put your main code here, to run repeatedly:
  adcValue = analogRead(analogPin);
  Serial.print("ADC Value = ");
  Serial.println(adcValue);

  delay(1000);

  if (adcValue == 1024)
    {
      kirimnotifikasi();
    }
}

void kirimnotifikasi() {
  WiFiClient client;
  if(client.connect(host, 80))
    {
      Serial.println("Connection Failed to Webserver");
      return;
    }

  String Link;
  Serial.println("Proses Kirim Notifikasi");

  Link = "http://8.219.209.62/kirimnotif.php";

  HTTPClient http;
  http.begin(client, Link);

  http.GET();
  http.end();

  delay(1000);
}
