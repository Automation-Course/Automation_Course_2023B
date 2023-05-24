#define led 4

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Servo.h>
#define gasSensorPin A0
const int buzzer =8;
const int threshold = 500;
Servo servo;
#define servoPin 9
int angle =0;
bool Direction;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  Serial.begin(9600);
  pinMode(gasSensorPin,INPUT);
  pinMode(led,OUTPUT);
  lcd.init();
  lcd.backlight();
servo.attach(servoPin);
servo.write(90);
pinMode(buzzer,OUTPUT);
}

void loop()
{
  int gasValue = analogRead(gasSensorPin); // Read the analog value from gasSensor
  //gasValue=map(gasValue,0,1024,0,255);
  lcd.setCursor(0, 4);
  lcd.clear();
  lcd.print("Systen ON"); 
  lcd.setCursor(10, 1);
  Serial.println(gasValue);
  delay(500);
  lcd.clear();
  
   if (gasValue < threshold) {
    digitalWrite(led, LOW);  
    Serial.println(gasValue);
    digitalWrite(buzzer,LOW);
    delay(500);
    Direction=false;
    lcd.clear();
    lcd.println("Gas Level is OK ");  
    delay(500);
    lcd.clear();
  }

      else if (gasValue > threshold) {
        digitalWrite(led,HIGH);
        tone(buzzer, 100,100);
        digitalWrite(buzzer,HIGH);
        delay(500);
        Serial.println(gasValue);
        Direction=true;
        lcd.clear();
        lcd.println("Gas Detected!    ");
         delay(1000);
         lcd.clear();
      }
      Fire();
}



void Fire() {
  if (Direction){
  angle=0;
}
else {
  angle=90;
}
servo.write(angle);
delay(15);
 }


