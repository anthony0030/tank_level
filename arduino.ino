#include <DHT.h>
#include <Ethernet.h>
#include <SPI.h>
#include <LiquidCrystal.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 }; // RESERVED MAC ADDRESS
EthernetClient client;

const float pi = 3.14;

#define TRIG 10      // Trigger pin
#define ECHO 13      // Echo pin
#define DHTPIN 2 // SENSOR PIN
#define DHTTYPE DHT11 // SENSOR TYPE - THE ADAFRUIT LIBRARY OFFERS SUPPORT FOR MORE MODELS

DHT dht(DHTPIN, DHTTYPE);

long previousMillis = 0;
unsigned long currentMillis = 0;
long interval = 250000; // READING INTERVAL

LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

int temprature = 0;  // TEMPERATURE VAR
int humidity = 0;  // HUMIDITY VAR
int tank_liters = 0;  // HUMIDITY VAR
String data;

int height = 2000;
int liters = 0;
int radius = 50;

void setup() { 
  Serial.begin(115200);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP"); 
  }

  dht.begin(); 
  delay(10000); // GIVE THE SENSOR SOME TIME TO START

  humidity = (int) dht.readHumidity(); 
  temprature = (int) dht.readTemperature(); 

  data = "";
}

void loop(){

  currentMillis = millis();
  if(currentMillis - previousMillis > interval) { // READ ONLY ONCE PER INTERVAL
    previousMillis = currentMillis;
    humidity = (int) dht.readHumidity();
    temprature = (int) dht.readTemperature();
  }

  data = "temp1=" + temprature + "&hum1=" + temprature + "&lit1=" + tank_liters;

  if (client.connect("www.*****.*************.com",80)) { // REPLACE WITH YOUR SERVER ADDRESS
    client.println("POST /add.php HTTP/1.1"); 
    client.println("Host: *****.*************.com"); // SERVER ADDRESS HERE TOO
    client.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: "); 
    client.println(data.length()); 
    client.println(); 
    client.print(data); 
  } 

  if (client.connected()) { 
    client.stop();  // DISCONNECT FROM THE SERVER
  }

  delay(300000); // WAIT FIVE MINUTES BEFORE SENDING AGAIN
}

int tank_calculator(){

}


