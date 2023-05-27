#include <Adafruit_LiquidCrystal.h>
#include <IRremote.h>

#include <Servo.h>

#include <LiquidCrystal_I2C.h>


//lcd
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <LiquidCrystal.h> // includes the LiquidCrystal Library
const int trigPin = 12;
const int echoPin = 10;
long duration;
int distanceCm, distanceInch;
void setup() {
  lcd.begin(16, 2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.setBacklight(1);

}
void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = (duration * 0.034 / 2)*100;
  distanceInch = duration * 0.0133 / 2;
  lcd.setCursor(0, 0); // Sets the location at which subsequent text written to the LCD will be displayed
  lcd.print("Distance: "); // Prints string "Distance" on the LCD
  lcd.print(distanceCm); // Prints the distance value from the sensor
    Serial.print("Distance: ");
  Serial.println(distanceCm);
  delay(10);

  delay(10);
}