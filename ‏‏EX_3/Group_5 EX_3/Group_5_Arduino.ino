// C++ code
//
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define BabyRoomLight 11
#define tempSensor 7 
#define servoPin 3 
#define LightSensor A3

LiquidCrystal_I2C lcd_1(0x27,16,2);
Servo WinterHeater;

//int BabyRoomLight=11;


int BabyRoomLightValue=0;
int BabyRoomLightBrightness;
double temp1;

double temp=25;
int inputTemp1 ;
int angle = 0; //init servo not to move


OneWire oneWire(tempSensor);
DallasTemperature sensors(&oneWire);

void setup()
{
lcd_1.begin(16, 2);
pinMode(tempSensor, INPUT);
pinMode(LightSensor,INPUT);
pinMode(BabyRoomLight,OUTPUT);
WinterHeater.attach(servoPin);
WinterHeater.write(0);
Serial.begin(9600);
}

void loop(void)
{
  sensors.requestTemperatures();

inputTemp1=analogRead(tempSensor);

float temp = sensors.getTempCByIndex(0);

CheckingTemp(temp);
delay(1500);

BabyRoomLightValue = analogRead(LightSensor); // Read analog value from light sensor
  ///Serial.println(BabyRoomLightValue); Checking the light value
  
  if (BabyRoomLightValue < 700) {
    ///Serial.println("Dark"); - for QA to understand if it's to dark
    BabyRoomLightBrightness = 255;  // Set full brightness
    digitalWrite(BabyRoomLight, BabyRoomLightBrightness);
  }  
  if (BabyRoomLightValue > 700) {
    ///Serial.println("Light");
    BabyRoomLightBrightness = 0;    // Set no brightness
    digitalWrite(BabyRoomLight, BabyRoomLightBrightness);  // Turn off the light
  }
  
} 


void CheckingTemp (double temp)
{
if (temp > 21 and temp < 29 ){
	lcd_1.clear();
  printScreen("The AC Is Off ");
  Turn_on_Fan (temp);
}

if (temp < 21){
      lcd_1.clear();
      printScreen("The Heat is ON");
      Turn_on_Fan(temp);
    }

if (temp > 28){
      lcd_1.clear();
      printScreen("The Cold is ON");
      Turn_on_Fan(temp);
    }
   
}

void Turn_on_Fan(double temp)	{
  if (temp > 21 and temp < 28) {
	    angle = 90;
  	}
  if (temp >= 28){
	    angle = 179;
	  }
  if (temp <=21) {
	    angle = 1;
  	}
   	WinterHeater.write(angle);
}

void printScreen (String print){
lcd_1.clear();
lcd_1.setCursor(0, 1);
lcd_1.print(print);
lcd_1.setBacklight(1);
}