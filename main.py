#include <DHT.h>
#define DHTPIN 4     // DHT11 sensor connected to GPIO 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C\tHumidity: ");
  Serial.print(humidity);
  Serial.println("%");

  delay(2000);
}
