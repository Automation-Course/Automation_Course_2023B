#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>




int ledRed = 7;
int servoPin = 9;
int buzzer = 10;
int ldrPin = A0;

int lightSensorValue = 0;
int lightMaxvalue=500;
int ldrValue = 0;
bool open =false;
bool close = false;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;


void setup() {
  Serial.begin(9600);
  pinMode(ledRed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ldrPin, INPUT);
  servo.attach(servoPin);
  lcd.init();
  lcd.clear();
  lcd.backlight();

}



void loop() {
  int sensorValue = analogRead(A1);
  lightMaxvalue=sensorValue;
  Serial.println(lightMaxvalue);
    lightSensorValue = analogRead(ldrPin);
    Serial.print("Light Sensor Value: ");
    Serial.println(lightSensorValue);
    delay(1000);
    // Check the light value
    if (lightSensorValue > lightMaxvalue) {
      if (open==false) {
      // Display "OPEN" on LCD 
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("OPEN CURTAIN");
      Serial.print("OPEN CURTAIN");
       // Turn servo to open position
      servo.write(180);
        for (int i = 0; i < 3; i++) {
          // Make buzzer sound
          digitalWrite(buzzer, LOW);
          digitalWrite(ledRed, HIGH);
          delay(200);
          digitalWrite(ledRed, LOW);
          delay(200);
        }
         servo.write(90);
        digitalWrite(buzzer, HIGH);
        open=true;
        close=false;
      }
    } else {
      if (close==false) { 
      // Display "CLOSED" on LCD and turn off LED
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("CLOSE CURTAIN");
      Serial.print("CLOSE CURTAIN");
         // Turn servo to close position
        servo.write(0);
        for (int i = 0; i < 3; i++) {
           // Make buzzer sound
         digitalWrite(buzzer, LOW);
          digitalWrite(ledRed, HIGH);
          delay(200);
          digitalWrite(ledRed, LOW);
          delay(200);
        }
        servo.write(90);
        digitalWrite(buzzer, HIGH);
        close=true;
        open=false;
      }
    }
  

 
}