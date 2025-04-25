 //Includes
#include <SPI.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include <MQUnifiedsensor.h>
#include "DHT.h"

//Definitions
#define micro "ESP-32"
#define Voltage_Resolution 3.3
#define pin 34 //Analog input 0 of your arduino
#define type "MQ-135" //MQ135
#define ADC_Bit_Resolution 12 // For arduino UNO/MEGA/NANO
#define RatioMQ135CleanAir 3.6//RS / R0 = 3.6 ppm  
#define DHTPIN 19
#define DHTTYPE DHT11
const int buzzerPin =  27;


//Data type assign
unsigned int pm1 = 0;
unsigned int pm2_5 = 0;
unsigned int pm10 = 0;
double CO2 = (0);

//WiFi Configuration
char* wifi_ssid = "juan";
char* wifi_password = "12345678";

//MQTT Configuration
char* mqtt_server = "192.168.137.1";
int mqtt_port = 1883;
char* mqtt_clientID = "";
char* mqtt_username = "";
char* mqtt_password = "";

//MQTT Topic Configuration
char *tempTopic = "temp";
char *humidTopic = "humid";
char *pm1Topic = "pm1";
char *pm2_5Topic = "pm2_5";
char *pm10Topic = "pm10";
char *co2Topic = "co2";
char *coTopic = "co";
char *alcoholTopic = "alcohol";
char *tolueneTopic = "toluene";
char *nh4Topic = "nh4";
char *acetoneTopic = "acetone";
int a;
char b;


void callback(char* topic, byte* payload, unsigned int length);

//Pin&Other things Assignment
WiFiClient espClient;
PubSubClient client(espClient);
//PubSubClient client(mqtt_server, mqtt_port, callback, espClient);

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial mySerial(21, 22); // RX, TX
int status = WL_IDLE_STATUS;
MQUnifiedsensor MQ135(micro, Voltage_Resolution, ADC_Bit_Resolution, pin, type);

void setup() {
  pinMode(buzzerPin, OUTPUT);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println();
  Serial.println("Serial port started!");


  // Initialize DHT11 sensor
  dht.begin();
  Serial.println("DHT initialized!");

  // Initialize Wifi Connection
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  //Initialize MQ135 Math Model
  //Set math model to calculate the PPM concentration and the value of constants
  MQ135.setRegressionMethod(1); //_PPM =  a*ratio^

  //Calibrate MQ135
  MQ135.init();
  Serial.print("Calibrating please wait.");
  float calcR0 = 0;
  for (int i = 1; i <= 10; i ++)
  {
    MQ135.update(); // Update data, the arduino will be read the voltage on the analog pin
    calcR0 += MQ135.calibrate(RatioMQ135CleanAir);
    Serial.print(".");
  }
  MQ135.setR0(calcR0 / 10);
  Serial.println("  done!.");

  //When Calibration failed, show this one
  if (isinf(calcR0)) {
    Serial.println("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your wiring and supply");
    while (1);
  }
  if (calcR0 == 0) {
    Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please check your wiring and supply");
    while (1);
  }
  //End of Calibration
  MQ135.serialDebug(false);
}

// Callback function
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Received message: ");
  Serial.println(topic);
  for(int i=0; i<length; i++){
    Serial.print((char) payload[i]);
    b=payload[i];
    Serial.println(b);
    a=b-'0';
    if(b=='1'){
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(buzzerPin, LOW);
      delay(1000);
      Serial.println("Buzzer ON");
    }
  }
  Serial.println();
}


//Connecting to WiFi
void setup_wifi()
{
  //Give a rest before connect, so ESP have time to scan wifi
  delay(100);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  //While connecting, print dots characters
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //When Connected, show Ip Adress and confirmation
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

//MQTT Connection
void reconnect() {
  // Loop MQTT connection until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    // Attempt to connect
    if (client.connect(mqtt_clientID, mqtt_username, mqtt_password)) {
      Serial.println("connected");
      client.subscribe("Buzzer");

      //When fail to connect to MQTT Server, retry until connected
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  float h = dht.readHumidity();
  float t = dht.readTemperature();


  
  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }
  else
    //Loop 1 (DHT11 reading)
  {
    String dataStr = "Humidity: " + String(h) + "%, Temperature: " + String(t);
    Serial.println(dataStr);

    if (client.connected())
    {
      String tempStr = "" + String(t) + "";
      String humidStr = "" + String(h) + "";
      client.publish(tempTopic, tempStr.c_str());
      client.publish(humidTopic, humidStr.c_str());
      Serial.println("DHT Data sent!");
      delay(1000);
    }
    int index = 0;
    char value;
    char previousValue;

    while (mySerial.available()) {
      value = mySerial.read();
      if ((index == 0 && value != 0x42) || (index == 1 && value != 0x4d)) {
        Serial.println("Cannot find the data header.");
        break;
      }

      if (index == 4 || index == 6 || index == 8 || index == 10 || index == 12 || index == 14) {
        previousValue = value;
      }
      else if (index == 5) {
        pm1 = 256 * previousValue + value;
        // Read PM1 Result
        // with unit ug/m3


        //Convert to string
        String dataStrpm1 = "PM1 Value: " + String(pm1) + "";

        //Check if convertion success
        Serial.println(dataStrpm1);

        //Convert to string, send data via MQTT
        String pm1Str = "" + String(pm1) + "";
        client.publish(pm1Topic, pm1Str.c_str());
        Serial.println("PM 1 Data sent!");
      }

      else if (index == 7) {
        pm2_5 = 256 * previousValue + value;
        // Print PM2.5 result
        // with unit ug/m3

        //convert result (pm2.5) to string
        String dataStrpm2_5 = "PM2_5 Value: " + String(pm2_5) + "";

        //check if convertion success
        Serial.println(dataStrpm2_5);

        //Convert to string, send data via MQTT
        String pm2_5Str = "" + String(pm2_5) + "";
        client.publish(pm2_5Topic, pm2_5Str.c_str());
        Serial.println("PM2.5 Data sent!");
      }

      else if (index == 9) {
        // Read PM10 value
        // with unit ug/m3
        pm10 = 256 * previousValue + value;

        //convert (pm1) to string
        String dataStrpm10 = "PM10 Value: " + String(pm10) + "";


        //Check if conversion succeed
        Serial.println(dataStrpm10);

        //Convert to string, send data via MQTT
        String pm10Str = "" + String(pm10) + "";
        client.publish(pm10Topic, pm10Str.c_str());
        Serial.println("PM10 Data sent!");

      }
      //If reading >15, back to first loop
      else if (index > 15) {
        break;
      }
      index++;
    }
    while (mySerial.available()) mySerial.read();
    {


      MQ135.update(); // Update data, the arduino will be read the voltage on the analog pin

      //Read Every data from MQ135
      MQ135.setA(110.47); MQ135.setB(-2.862);
      CO2 = MQ135.readSensor();

      MQ135.setA(605.18); MQ135.setB(-3.937);
      float CO = MQ135.readSensor();

      MQ135.setA(77.255); MQ135.setB(-3.18);
      float Alcohol = MQ135.readSensor();

      MQ135.setA(44.947); MQ135.setB(-3.445);
      float Toluene = MQ135.readSensor();

      MQ135.setA(102.2 ); MQ135.setB(-2.473);
      float NH4 = MQ135.readSensor();

      MQ135.setA(34.668); MQ135.setB(-3.369);
      float Acetone = MQ135.readSensor();


      //////////Converting, Displaying on Serial Monitor
      //////And then publish them into MQTT

      //Convert data from CO2 into String
      String dataStrCO2 = "CO2 Value: " + String(CO2) + "";
      //CO2 Conversion check
      Serial.println(dataStrCO2);

      //Change CO2 data type to string, and publish to MQTT
      String CO2Str = "" + String(CO2) + "";
      client.publish(co2Topic, CO2Str.c_str());
      Serial.println("CO2 Data sent!");


      //Convert data from CO into String
      String dataStrCO = "CO Level: " + String(CO) + "";
      //CO Conversion check
      Serial.println(dataStrCO);

      //Change data type to string, and publish to MQTT
      String COStr = "" + String(CO) + "";
      client.publish(coTopic, COStr.c_str());
      Serial.println("CO Data sent!");


      //Convert data from Alcohol into String
      String dataStrAlcohol = "Alcohol Level: " + String(Alcohol) + "";
      //Alcohol Conversion check
      Serial.println(dataStrAlcohol);

      //Change data type to string, and publish to MQTT
      String AlcoholStr = "" + String(Alcohol) + "";
      client.publish(alcoholTopic, AlcoholStr.c_str());
      Serial.println("Alcohol Data sent!");


      //Convert data from Toluene into String
      String dataStrToluene = "Toluene Level: " + String(Toluene) + "";
      //Toluene Conversion check
      Serial.println(dataStrToluene);

      //Change data type to string, and publish to MQTT
      String TolueneStr = "" + String(Toluene) + "";
      client.publish(tolueneTopic, TolueneStr.c_str());
      Serial.println("Toluene Data sent!");


      //Convert data from NH4 into String
      String dataStrNH4 = "NH4 Value: " + String(NH4) + "";
      //NH4 Conversion check
      Serial.println(dataStrNH4);

      //Change data type to string, and publish to MQTT
      String NH4Str = "" + String(NH4) + "";
      client.publish(nh4Topic, NH4Str.c_str());
      Serial.println("NH4 Data sent!");


      //Convert data from Acetone into String
      String dataStrAcetone = "Acetone Level: " + String(Acetone) + "";
      //Acetone Conversion check
      Serial.println(dataStrAcetone);

      //Change data type to string, and publish to MQTT
      String AcetoneStr = "" + String(Acetone) + "";
      client.publish(acetoneTopic, AcetoneStr.c_str());
      Serial.println("Acetone Data sent!");

      Serial.println("All Data Sent :D.");
      Serial.println("Rest 10 Seconds");
      //Delay, and Query again
      delay(10000);
    }

  }
}
