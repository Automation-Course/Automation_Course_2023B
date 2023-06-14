#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define LdrPin  A0 // the cell and 10K pulldown are connected to a0
int LdrValue=0; // the analog reading from the sensor divider
#define LedPin  6// connect Red LED to pin 11 (PWM pin)
int LedBrightness; 


LiquidCrystal_I2C lcd(0x27, 16, 2);


const int trigPin = 4;
const int echoPin = 5;

Servo servo_11;


void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode (11,INPUT);
  pinMode(LdrPin,INPUT);
  pinMode(LedPin,OUTPUT);


  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.setBacklight(LOW); // Set the backlight to be initially off
  lcd.print("Distance: ");
  
  servo_11.attach(11);
  servo_11.write(0);
}

void loop() {
  long duration, distance;

  // Send ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the response
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm
  distance = duration / 58.2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  lcd.setCursor(10, 0);
  lcd.print("       "); // Clear the previous distance value
  lcd.setCursor(10, 0);
  lcd.print(distance);
  lcd.print("cm");
  
  
  
  // Check if the object is closer than 20 cm
  if (distance < 20) {

    // Display message on the LCD screen
    lcd.setBacklight(HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Object detected!");
    

     LdrValue = analogRead(LdrPin); 
    Serial.print("LDR reading = ");
    Serial.println(LdrValue);    // the raw analog reading
    LedBrightness = map(LdrValue, 700, 6, 0, 255);
    Serial.print("LDR brightness = ");
    Serial.println(LedBrightness);
    analogWrite(LedPin, LedBrightness );
    servo_11.write(0);
    }


   else {

    // Clear message on the LCD screen
    lcd.setBacklight(LOW);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    servo_11.write(90);
     digitalWrite(LedPin, LOW);

    
  }

}