#include <DHT.h> //library for TEP&HUM SENSOR
#include <Ethernet.h> //library for ETHERNET
#include <DS3231.h> //library for RTC

byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0x01 }; // RESERVED MAC ADDRESS
EthernetClient client;

const float pi = 3.14;
const int tank_height = 2000;
const int tank_radius = 50;


#define TRIG 8      // Trigger pin
#define ECHO 7      // Echo pin
#define DHTPIN 2 // SENSOR PIN
#define DHTTYPE DHT11 // SENSOR TYPE - THE ADAFRUIT LIBRARY OFFERS SUPPORT FOR MORE MODELS

DHT dht(DHTPIN, DHTTYPE);

DS3231  rtc(SDA, SCL);

long previousMillis = 0;
unsigned long currentMillis = 0;
long interval = 250000; // READING INTERVAL


int temprature = 0;  // TEMPERATURE VAR
int humidity = 0;  // HUMIDITY VAR
float liters = 0;  // liters VAR
String data;


void setup() { 
  Serial.begin(115200);
  Serial.println("********** START BOOT **********");

  //if (Ethernet.begin(mac) == 0) {
    //Serial.println("Failed to configure Ethernet using DHCP"); 
  //}



  dht.begin(); 
   for (int i=0; i <= 100; i+=10){ // GIVE THE SENSOR SOME TIME TO START
      Serial.print("Starting ");
      Serial.print("DHT");
      Serial.print(DHTTYPE); 
      Serial.print(" Sensor"); 
      Serial.print("...");
      Serial.print(i); 
      Serial.println("%");
     delay(1000);
   } 
  Serial.println("***** Started DHT Sensor *****");  
   
   rtc.begin(); 
   for (int i=0; i <= 100; i+=25){ // GIVE THE RTC SOME TIME TO START
      Serial.print("Starting ");
      Serial.print("RTC"); 
      Serial.print("...");
      Serial.print(i); 
      Serial.println("%");
     delay(100);
   } 
  Serial.println("***** Started RTC *****");  

  humidity = (int) dht.readHumidity(); 
  temprature = (int) dht.readTemperature();
  liters = tank_liters(); 

  data = "";


  // The following lines can be uncommented to set the date and time
  rtc.setDOW(SATURDAY);     // Set Day-of-Week to SUNDAY
  rtc.setTime(16, 46, 0);     // Set the time to 12:00:00 (24hr format)
  rtc.setDate(16, 4, 2016);   // Set the date to January 1st, 2014


  
  Serial.println("********** END BOOT **********");
}

void loop(){
  currentMillis = millis();
  if(currentMillis - previousMillis > interval) { // READ ONLY ONCE PER INTERVAL
    previousMillis = currentMillis;
    data_out();
  }

  data_in();
  serial_print();
  delay(3000); // WAIT 3 seconds
}

void data_in(){
  liters = tank_liters();
  humidity = (int) dht.readHumidity();
  temprature = (int) dht.readTemperature();
}


void data_out(){
//  data = "temp1=" + temprature + "&hum1=" + temprature + "&lit1=" + liters;

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
  tank_full = tank_height - tank_emty;
  return ((pi*pow(tank_radius, 2)) * tank_full);
}



void serial_print(){
  
  Serial.print("date = ");
  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");
  // Send time
  Serial.println(rtc.getTimeStr());
  
  Serial.print("temprature = ");
  Serial.print(temprature);
  Serial.println("*C");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println("%");
  
  Serial.print("liters = ");
  Serial.print(tank_liters());
  Serial.println("");
  Serial.println("");
}
