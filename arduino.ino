#include <DHT.h>
#include <Ethernet.h>
#include <SPI.h>
#include <LiquidCrystal.h>

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 }; // RESERVED MAC ADDRESS
EthernetClient client;

const float pi = 3.14;
const int tank_height = 2000;
const int tank_radius = 50;


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
float tank_liters = 0;  // liters VAR
String data;


void setup() { 
  Serial.begin(115200);

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
  currentMillis = millis();
  if(currentMillis - previousMillis > interval) { // READ ONLY ONCE PER INTERVAL
    previousMillis = currentMillis;
    data_out();
  }

  data_in();
  print_lcd();
  delay(3000); // WAIT 3 seconds
}

void data_in(){
  liters = tank_liters();
  humidity = (int) dht.readHumidity();
  temprature = (int) dht.readTemperature();
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

float tank_liters(){
  long duration , tank_emty , tank_full;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH);
  tank_emty = ((duration/2) / 29.1);
  tank_full = tank_height - tank_emty
  return ((pi*pow(radius, 2)) * tank_full);
}

void print_lcd(){
 //script ot print the data to the lcd
}

void print_lcd_welcome(){
 //script ot print the data to the lcd
}