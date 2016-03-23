/******************************************************
 * Stelios Mantzaris                                  *
 * Water Tank Level Display                           *
 * based on code found in:                            *
 * http://goo.gl/l6ssa                                *
 * 01/2013                                            *
 * CC - Distribute & Change freely to suit your needs *
 ******************************************************/

#include <LiquidCrystal.h>

#define TRIG 10      // Trigger pin
#define ECHO 13      // Echo pin
#define BUZZER_PIN 8 // Buzzer pin
#define SWITCH_INT 0 /* 0 => pin 2 */
#define CAPACITY_BASE (L_LENGTH * H_HEIGHT * W_WIDTH)/1000000
#define SIZE_BAR (16 * 5)
#define DISTANCE_PLUS 10 /* cm (distance plus from water to sonar*/ 
#define L_LENGTH 150.0 /* cm */
#define H_HEIGHT 40.0 /* cm */
#define W_WIDTH 50.0 /* cm */
#define THRESHOLD_ALARM_1 0 /* cm */
#define THRESHOLD_ALARM_2 40 /* cm */
#define DELAY_0 600 /* ms; 1000 * 60 * 1 = 1 min */
#define DELAY_1 600 /* ms */
#define DELAY_2 200 /* ms */

/* initialize the library with the numbers of the interface pins */
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

float tempC;      // compute temp
int readingC;     // analog reading
int tempPinC = 0; // LM35 analog port
int mute = 0;     // mute button pin
int LABEL = 1;

void setup() {
  analogReference(INTERNAL); // use arduino internal reference

  /* set up the LCD's number of rows and columns: */
  lcd.begin(16, 2);

  pinMode(BUZZER_PIN, OUTPUT);

  /**
   * LOW to trigger the interrupt whenever the pin is low,
   * CHANGE to trigger the interrupt whenever the pin changes value
   * RISING to trigger when the pin goes from low to high,
   * FALLING for when the pin goes from high to low. 
   */
  attachInterrupt(SWITCH_INT, button, RISING);
  
  /* initialize serial communication */
  Serial.begin(9600);
}

void loop() {
  readingC = analogRead(tempPinC);
  tempC = readingC / 9.31;
  //tempC = (1.1 * readingC *100)/1024;
  
 if (LABEL <=1){
    lcd.clear();
    lcd.setCursor(0, 0); 
    lcd.print("Water Tank Level");
    lcd.setCursor(0, 1); 
    lcd.print("by St. Mantzaris");
    delay(8000);
    }
  
  LABEL =2;
  
  long hWaterCm;
  int liters;

  hWaterCm = read_height();
  if (check_alarm(hWaterCm) != 0) /* read again water height */
    hWaterCm = read_height();

  lcd.clear();

  print_histogram(hWaterCm);
  
  lcd.setCursor(0, 1);
  String empty_t="Empty";
  String full_t="Full";
  
 if (hWaterCm >=40){
    lcd.print(full_t);
    lcd.print(" 120");
    lcd.print("L ");
    lcd.setCursor(10, 1);
    lcd.print(tempC);
    lcd.setCursor(14, 1);
    lcd.print("C");

}
 
  if (hWaterCm <=0){
    lcd.print(empty_t);
    lcd.print(" 0");
    lcd.print("L ");
    lcd.setCursor(10, 1);
    lcd.print(tempC);
    lcd.setCursor(14, 1);
    lcd.print("C");
  }
      else {
      lcd.print(hWaterCm);
      lcd.print("cm-");
      // liters = CAPACITY_BASE * (hWater / 100.0) * 1000
      liters = floor(CAPACITY_BASE * hWaterCm * 10);
      lcd.print(liters);
      lcd.print("L ");
      lcd.setCursor(10, 1);
      lcd.print(tempC);
      lcd.setCursor(14, 1);
      lcd.print("C");
     }
  lcd.setCursor(15, 1);
  if (!mute)
  lcd.print('_');
  else
  lcd.print('x');

  switch (check_alarm(hWaterCm)) {
  case 1:
    //full - alarm

    buzz(200);
    delay(100);
    buzz(200);
    delay(100);
    buzz(200);
    delay(100);
    buzz(200);
    delay(100);
    buzz(200);
    delay(100);
    buzz(200);
    delay(100);
    buzz(200);
    delay(100);
    buzz(200);
    break;

  case 2:
    //empty - alarm

    buzz(200);
    delay(200);
    buzz(200);
    delay(DELAY_2);
    break;

  case 0: // no alarm
    //normal - no alarm
    delay(DELAY_0);
  }
}

/* Compute & Display Histogram Capacity Bar */
void print_histogram(int hWaterCm) {
  int i;
  int bloks;
  float histogram;

  // hWaterCm : H_HEIGHT = histogram : SIZE_BAR
  histogram = (SIZE_BAR * hWaterCm) / H_HEIGHT;
  histogram = histogram + 0.5;

  bloks = (int)histogram / 5;

  for (i = 0; i < bloks; i++)
    lcd.write(5);
  
  if ((int)(histogram) % 5 > 0)
    lcd.write((int)(histogram) % 5);
}

long read_height() {
  /**
   * establish variables for duration of the ping, 
   * and the distance result in centimeters:
   */
  long hWaterCm;

  pinMode(TRIG, OUTPUT);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  pinMode(ECHO, INPUT);
  float distance = pulseIn(ECHO, HIGH);
  distance=distance / 29.387 / 2;
  Serial.println(distance);
  delay(500);
 
  /* convert the time into a distance */
   hWaterCm = H_HEIGHT - distance + DISTANCE_PLUS;
  if (hWaterCm < 0)
    return 0;

  if (hWaterCm > H_HEIGHT)
    return H_HEIGHT;

  return hWaterCm;
}

void buzz(int msec) {
  if (!mute)
  digitalWrite(BUZZER_PIN, HIGH);
  delay(msec);
  digitalWrite(BUZZER_PIN, LOW);
}

int check_alarm(int hWaterCm) {
  if (hWaterCm >= THRESHOLD_ALARM_2) {
  return 1;}
  if (hWaterCm <= THRESHOLD_ALARM_1) {
  return 2;}
else {   return 0;}
}

void button() {
  mute = !mute;
  lcd.setCursor(15, 1);
  if (!mute)
  lcd.print('_');
  else
  lcd.print('x');
}
