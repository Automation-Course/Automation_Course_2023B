#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 


const int servoPin = 5;
const int ledPin = 3;
const int ldrPin = A0;

long cm = 101;
int ldr = 0;
int counter = 0;
bool flag = true;
int angle = 0;


Servo servoMotor;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}


void setup() {
 
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin , INPUT);
  servoMotor.attach(servoPin);
  servoMotor.write(90);
  
  lcd.init();
  lcd.backlight();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Door Status:");
  
  Serial.begin(9600);
}

void loop() {

  // for the night light
   int ldr = analogRead(ldrPin);
  
  // Check if light level is below the threshold
  if (ldr > 200) {
    counter += 1;
    if (counter <= 255){
      analogWrite(ledPin, counter); // Turn on the LED
    }
    else {
      analogWrite(ledPin, 255); // Turn on the LED max value
    }
  } 
  else {
    counter = 0;
    analogWrite(ledPin, 0); // Turn off the LED
  }


  // convert the time into a distance
  cm = 0.01723 * readUltrasonicDistance(7, 6);
  lcd.setCursor(3, 1);
  lcd.setCursor(0, 1); // Set cursor to the second row
  
  if (cm <= 20) 
  {
    if(angle >= 0 && angle < 15)
    {
     angle += 1;
     servoMotor.write(100);
     lcd.print("Open Door!"); // Make sure to overwrite any previous text
     Serial.print("open: value is->");
     Serial.println(cm);
    }
    else
      servoMotor.write(90);
  }
  if (cm > 20) 
  {
    if(angle > 0)
    {
      angle -= 1;
      servoMotor.write(83);
      lcd.print("close Door!"); // Make sure to overwrite any previous text
    }
    else
      servoMotor.write(90);
  }

  Serial.println("Distance Sensor is reading");
  Serial.print("this cm-> ");
  Serial.println(cm);
  Serial.print("Ldr value is->");
  Serial.println(ldr);
  Serial.print("counter value is->");
  Serial.println(counter);
  Serial.print("angle value is->");
  Serial.println(angle);
}
