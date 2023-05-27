#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo myServo;
const int servoPin = 9;
int initial = 0;

int inputPin = 11;
int PIRpin = 8;
int pirState = LOW;
int val = 0;
int photocellPin = 0;
int photocellReading;

LiquidCrystal_I2C lcd(0x27, 16, 2); // Set the LCD I2C address (0x27) and size (16x2)

void setup() {
  myServo.attach(servoPin);
  pinMode(inputPin, OUTPUT);
  pinMode(PIRpin, INPUT);
  pinMode(photocellPin, INPUT);

  Serial.begin(9600);

  lcd.begin(16, 2); // Initialize the LCD with the specified size
  lcd.backlight(); // Turn on the LCD backlight
  lcd.setCursor(0, 0);
  lcd.print("P.I.R Motion");
  lcd.setCursor(0, 1);
  lcd.print("and Light Sensor");
  delay(2000);

  lcd.clear();
  lcd.init();	


  lcd.setCursor(0, 0);
  lcd.print("Waiting For");
  lcd.setCursor(0, 1);
  lcd.print("Motion....");
}

void loop() {
  val = digitalRead(PIRpin);
  photocellReading = analogRead(photocellPin);

  if (val == HIGH) {
    digitalWrite(inputPin, HIGH);

    if (pirState == LOW) {
      Serial.println("Motion Detected!");
      lcd.clear();
      initial = 100;
      myServo.write(initial);
      lcd.setCursor(0, 0);
      lcd.print("Motion Detected!");
      lcd.setCursor(0, 1);
      lcd.print("Bulb is ON");
      pirState = HIGH;
    }
  } else {
    digitalWrite(inputPin, LOW);
    if (pirState == HIGH) {
      Serial.println("Motion Ended!");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Motion Ended!");
      initial =90;
      myServo.write(initial);
      lcd.setCursor(0, 1);
      lcd.print("Bulb is OFF");
      pirState = LOW;
      delay(500);
    }
  }
}