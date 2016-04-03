#include <DHT.h>
#include <Ethernet.h>
#include <SPI.h>
#include <LiquidCrystal.h>
#include <dht11.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 }; // RESERVED MAC ADDRESS
byte ip[] = { 192, 168, 1, 117 }; // RESERVED IP ADDRESS
EthernetClient client;

const float pi = 3.14159265359;
const int tank_height = 2000;
const int tank_radius = 50;
const float tank_liters = 0;
const float tank_liters_missing = 0;


#define TRIG 10      // Trigger pin
#define ECHO 13      // Echo pin
#define DHTPIN 2 // SENSOR PIN
#define DHTTYPE DHT11 // SENSOR TYPE - THE ADAFRUIT LIBRARY OFFERS SUPPORT FOR MORE MODELS

DHT dht(DHTPIN, DHTTYPE);



LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

int temprature = 0;  // TEMPERATURE VAR
int humidity = 0;  // HUMIDITY VAR
float tank_liters_current = 0;  // liters VAR
String data;


void setup() { 
  Serial.begin(115200);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP"); 
  }

  dht.begin(); 
  delay(10000); // GIVE THE SENSOR SOME TIME TO START

  humidity = (int) dht.readHumidity(); 
  temprature = (int) dht.readTemperature();
  liters = tank_liters(); 

  data = "";
}

void loop(){
  da


}


void tank_Liters(){
  long duration, missing_cm;

  digitalWrite(TRIG, LOW); 
  delayMicroseconds(2); 

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10); 
 
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  missing_cm = duration/58.2;


  tank_liters_missing = (pi*tank_radius*missing_cm);

  tank_liters_current = tank_liters - tank_liters_missing;
}


void print_lcd(){
 //script ot print the data to the lcd
}

void print_lcd_welcome(){
 //script ot print the data to the lcd
}

void log_to_sd(){
 //script ot print the data to sd card
}

void data_out(){
  data = "temp1=" + temprature + "&hum1=" + temprature + "&lit1=" + liters;

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
}

void data_in(){
  liters = tank_liters();
  humidity = (int) dht.readHumidity();
  temprature = (int) dht.readTemperature();
}