// C++ code
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

LiquidCrystal_I2C lcd_1(0x27, 16, 2);

#define RED_LED_PIN 12
#define GREEN_LED_PIN 13
#define SERVO_PIN 3 
#define PHOTO_SENSOR_PIN A1
#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);
bool once= false;
bool twice = false;
int sensorValue = 0;
int threshold = 100;
Servo myservo;
DallasTemperature sensors(&oneWire);

void setup() // set up the system
{
  	lcd_1.init();
    lcd_1.begin(17,2);
    lcd_1.backlight();
  	pinMode(PHOTO_SENSOR_PIN, INPUT);
  	pinMode(GREEN_LED_PIN,OUTPUT);
    pinMode(RED_LED_PIN,OUTPUT);
    myservo.attach(SERVO_PIN);
  	Serial.begin(9600);
    sensors.begin();
}

void loop()
{
  sensors.requestTemperatures(); 
  sensorValue = analogRead(PHOTO_SENSOR_PIN);
  if(sensorValue < threshold || sensors.getTempCByIndex(0) > 27) // if that checks the temp and the resist from the light
  {
    light_led(GREEN_LED_PIN,0);
    light_led(RED_LED_PIN,255);
    if(!once)// if that make sure the state of the curtain
    {
       lcd_print("Closed");
       once = true;
       twice = false;
      rotate(0);
      Serial.println(sensors.getTempCByIndex(0));
    }
  }
  else
  {
    light_led(GREEN_LED_PIN,255);
    light_led(RED_LED_PIN,0);
    if(!twice)// if that make sure the state of the curtain
    {
       lcd_print("Open");
       twice = true;
       once = false;
      rotate(180);
      Serial.println(sensors.getTempCByIndex(0));
    }
  }
}

void rotate(int speed) // function that sets the speed to the servo
{     
      myservo.write(speed);
	     delay(900);   
       myservo.write(90);
}

void lcd_print(String state){ // function that prints to the lcd screen
    lcd_1.clear();
    lcd_1.setCursor(0, 0); // Set cursor to first column of first row
	  lcd_1.print("Curtain Is");
	  lcd_1.setCursor(0, 1); // Set cursor to first column of second row
	  lcd_1.print(state);
}

void light_led(int port , int power) // function that sets a light power to the led 
{
  digitalWrite(port, power);
}