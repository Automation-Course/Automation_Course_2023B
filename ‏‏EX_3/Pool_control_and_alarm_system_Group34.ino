
// C++ code
//
#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>


int led = 7;
const char buttonpin = 2;
float temp_sen = 4;
LiquidCrystal_I2C lcd(0x27,16,2);

#define servoPin  9
Servo servo;

OneWire oneWire(temp_sen);
DallasTemperature sensors(&oneWire);

int speed = 90;
bool ServoOn = false; 
float temp;
int buttonstate = 0;

void setup()
{
  sensors.begin();
  pinMode(led, OUTPUT);
  pinMode(buttonpin, INPUT);
  servo.attach(servoPin);
  Serial.begin(9600);
  lcd.backlight(); 
}

void loop()
{ 
  Serial.print("The button state is: ");
  Serial.println(ServoOn);
  buttonstate = digitalRead(buttonpin);
  if(buttonstate == 1){
    Serial.println("high");
    if(ServoOn == false){
      ServoOn = true;
    }
    else{
      ServoOn = false;
    }
  }
  sensors.requestTemperatures(); 
  temp = sensors.getTempCByIndex(0);
  
  Serial.print("Celsius temperature: ");
  Serial.println(temp); 
  if(temp > 28){
    lcd.begin(16, 2);
    lcd.print("Put sunscreen!");
    servo.write(180);
    digitalWrite(led, LOW);
    if(temp > 33) {
      digitalWrite(led, HIGH);
      lcd.begin(16, 2);
      lcd.print("Sit in the shade");
    }
    
  }
  else{
    lcd.begin(16, 2);
    lcd.print("Have a nice tan!");
    digitalWrite(led, LOW);
    if(ServoOn == true){
      servo.write(180);
    }
    else{
      servo.write(90);
    }
    speed = 90;
  }
 
}


void ventilate(){
  servo.write(180);
}
