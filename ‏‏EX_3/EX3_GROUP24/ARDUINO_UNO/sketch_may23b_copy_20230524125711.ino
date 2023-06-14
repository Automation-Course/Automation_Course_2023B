
// Automated Cooling system

// libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>


// define pins
int tempSensor = 5;
int echoPin = 2;  //blue
int trigPin = 3;  //purple
int ledBlue = 4;
int servoPin = 9;


// define variables
int max_dist = 20; // max distance that the sensor will detect
//int max_temp = 25; // max temperature that the sensor will detect
float duration; // time for the return of the pulse
float distance = -1; // one-way distance of the pulse (-1 indicates no valid distance yet)
int ldrValue = 0;
double celsius = 0;
int angle = 0;
int speed = 0;
bool direction = true;

LiquidCrystal_I2C lcd_1(0x27, 16, 2);
Servo servo;
OneWire oneWire(tempSensor);
DallasTemperature sensors(&oneWire);

// Time-related variables
unsigned long currentTime;
unsigned long previousTime = 0;
const unsigned long interval = 2000; // 2 seconds

// State variables
bool welcomeShown = false;

void setup()
{
  sensors.begin();

  lcd_1.init();
  lcd_1.begin(16, 2); // initialize the LCD
  lcd_1.backlight(); // turn on the backlight

  // define I/O
  pinMode(tempSensor, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(servoPin, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  pinMode(trigPin, OUTPUT);

  servo.attach(servoPin);
  servo.write(0); // stay put
  Serial.begin(9600);
}

void loop()
{
  currentTime = millis();

  sensors.requestTemperatures();
  float temperatureCelsius = sensors.getTempCByIndex(0);
  Serial.print("Celsius temperature: ");
  Serial.println(temperatureCelsius);

  // Check if it's time to show the welcome message
  if (!welcomeShown)
  {
    printScreen("Welcome Home!");
    welcomeShown = true;
    previousTime = currentTime;
  }

  // Check if it's time to perform ultrasonic scanning
  if (currentTime - previousTime >= 20)
  {
    ultrasonic_scanning();
    previousTime = currentTime;
  }

  // Check if it's time to show the detection approval
  if (distance <= max_dist && temperatureCelsius >= 26.5)
  {
    detection_approved();
    previousTime = currentTime;
  }
}

// FUNCTIONS
void ultrasonic_scanning()
{
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);

  // calculating the distance of the pulse
  distance = (duration * 0.034) / 2;
 // Serial.println(distance);
}

// print string only
void printScreen(String print)
{
  lcd_1.print(print);
  lcd_1.setCursor(0, 1);
  lcd_1.backlight();
  unsigned long printStartTime = millis();
  while (millis() - printStartTime < 2000)
  {
    // Wait for 2 seconds
  }
  lcd_1.clear();
  lcd_1.backlight();
}

// print combined message
void printValOnScreen(String print, int val, String units)
{
  lcd_1.backlight();
  lcd_1.print(print);
  lcd_1.setCursor(print.length(), 0);
  lcd_1.print(val);
  lcd_1.print(" ");
  lcd_1.print(units);
  lcd_1.setCursor(0, 1);
  unsigned long printStartTime = millis();
  while (millis() - printStartTime < 2000)
  {
    // Wait for 2 seconds
  }
  lcd_1.clear();
  lcd_1.backlight();
}

void detection_approved()
{
  printValOnScreen("Eyal at ", distance, " cm");
  startEngine();
  blink(ledBlue);
}

void startEngine()
{
  if (direction)
  {
    angle += 1;
    speed = 180;
  }
  else
  {
    angle -= 1;
    speed = 0;
  }
  servo.write(speed);
}

void blink(int led)
{
  digitalWrite(led, HIGH); // set the led on
  unsigned long blinkStartTime = millis();
  while (millis() - blinkStartTime < 100)
  {
    // Wait for 100 milliseconds
  }
  digitalWrite(led, LOW); // turn the LED off
  while (millis() - blinkStartTime < 200)
  {
    // Wait for 100 milliseconds
  }
}