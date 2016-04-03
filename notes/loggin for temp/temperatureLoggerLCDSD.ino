#include <OneWire.h>
#include <DallasTemperature.h>
#include <SD.h>
#include <string.h>
#include <LiquidCrystal.h>
int counterTemp = 0;
float dataInt;
char test[20];

const int chipSelect = 4; 
#define ONE_WIRE_BUS 7
String dataString; 

OneWire oneWire(ONE_WIRE_BUS);
File myFile; 
DallasTemperature sensors(&oneWire);

int backLight = 14;   
LiquidCrystal lcd(15, 16, 17, 5, 4, 3, 2);
void setup(void)
{
   pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); 

 lcd.begin(16, 2);
  dataString.reserve(4);
  pinMode(10, OUTPUT);

  Serial.begin(57600);
  Serial.println("card initialized.");

  sensors.begin();
  Serial.print(sensors.getDeviceCount(), DEC);
   // SET UP SD CARD FOR WRITING
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  } else {
    Serial.println("SD card initialized");
    myFile = SD.open("temper1.txt", FILE_WRITE);    // open file for writing
    if (myFile) {  // if file can be opened, write to it
      Serial.print("temper1.txt file opened for writing");
      myFile.close();
    } else {  // if not, show an error
      Serial.println("ERROR: not able to open temperature.txt");
    }
  }
 
  
 
  
}
 
 
void loop(void)
{
  lcd.setCursor(0, 0); 
  sensors.requestTemperatures(); // Send the command to get temperatures


  lcd.print(sensors.getTempCByIndex(0));  
   dataString = "";
   dataInt = 0;
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
 // Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
//  Serial.println("DONE");

 Serial.print("Temperature for Device 1 is: ");
 if(sensors.getTempCByIndex(0) < 0){
 dataInt = 0;
 }
  else{
    dataInt = sensors.getTempCByIndex(0);
  }

  Serial.print(floatToString(test, dataInt, 1, 5)); 
 
 delay(1000);   
 writeDataToCard(counterTemp, dataInt);
  
  delay(59000);
  counterTemp++;
}

void writeDataToCard(int time, float dataInt) {
  myFile = SD.open("temper.txt", FILE_WRITE);
  myFile.print(time);
  myFile.print(", ");
  myFile.print(floatToString(test, dataInt, 1, 5));
  myFile.print("\n");
  myFile.close();
}




char * floatToString(char * outstr, double val, byte precision, byte widthp){
  char temp[16];
  byte i;

  // compute the rounding factor and fractional multiplier
  double roundingFactor = 0.5;
  unsigned long mult = 1;
  for (i = 0; i < precision; i++)
  {
    roundingFactor /= 10.0;
    mult *= 10;
  }
  
  temp[0]='\0';
  outstr[0]='\0';

  if(val < 0.0){
    strcpy(outstr,"-\0");
    val = -val;
  }

  val += roundingFactor;

  strcat(outstr, itoa(int(val),temp,10));  //prints the int part
  if( precision > 0) {
    strcat(outstr, ".\0"); // print the decimal point
    unsigned long frac;
    unsigned long mult = 1;
    byte padding = precision -1;
    while(precision--)
      mult *=10;

    if(val >= 0)
      frac = (val - int(val)) * mult;
    else
      frac = (int(val)- val ) * mult;
    unsigned long frac1 = frac;

    while(frac1 /= 10)
      padding--;

    while(padding--)
      strcat(outstr,"0\0");

    strcat(outstr,itoa(frac,temp,10));
  }

  // generate space padding 
  if ((widthp != 0)&&(widthp >= strlen(outstr))){
    byte J=0;
    J = widthp - strlen(outstr);
    
    for (i=0; i< J; i++) {
      temp[i] = ' ';
    }

    temp[i++] = '\0';
    strcat(temp,outstr);
    strcpy(outstr,temp);
  }
  
  return outstr;
}
