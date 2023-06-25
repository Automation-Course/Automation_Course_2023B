//Safe Air Sensor Gas System 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <NewPing.h> // Library for ultrasonic distance sensor


const int sensorGas = 2; //???
const int GreenLed = 3;
const int RedLed = 4;
const int buzzer = 5;
const int servopin = 6;
const int triggerPin = 7; // Ultrasonic sensor trigger pin
const int echoPin = 8; // Ultrasonic sensor echo pin
const int maxDistance = 100; // Maximum distance to detect gas in centimeters
const int blinkInterval = 1000;

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;
NewPing distanceSensor(triggerPin, echoPin, maxDistance); // Create an instance of the distance sensor


bool isLedOn = false;
bool gasDetected = false;
unsigned long previousMillis = 0;
unsigned long activationStartTime = 0;
unsigned long activationDuration = 0;

void setup() {
  pinMode(sensorGas, INPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(RedLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(triggerPin, OUTPUT); // set the trigPin as an Output
	pinMode(echoPin, INPUT); // set the echoPin as an Input
  lcd.init();
  lcd.backlight(1);
}

void loop() {
  unsigned long currentMillis = millis();

  // Read the distance from the ultrasonic sensor
  int distance = distanceSensor.ping_cm();
  lcd.scrollDisplayLeft();
  delay(1000);

  if (distance <= maxDistance) { // Check if distance is within the gas detection range
    if (digitalRead(sensorGas) == 0) {
      if (!gasDetected) {
        gasDetected = true;
        activationStartTime = currentMillis;
      }

      // Gas detected
      digitalWrite(RedLed, HIGH);
      digitalWrite(buzzer, HIGH);
      digitalWrite(GreenLed, LOW);
      servo.attach(servoPin);
      servo.write(0);
      lcd.setCursor(0, 0);
      lcd.print("  Beware!!  ");
      lcd.setCursor(0, 1);
        lcd.print(" Gas in area!! ");

      if (currentMillis - previousMillis >= blinkInterval) {
        previousMillis = currentMillis;
        isLedOn = !isLedOn;
        digitalWrite(RedLed, isLedOn ? HIGH : LOW);
      }
      
    } else {
      if (gasDetected) {
        // Gas detection stopped
        activationDuration = currentMillis - activationStartTime;
        gasDetected = false;
        activationStartTime = 0;

        digitalWrite(buzzer, LOW);
        digitalWrite(RedLed, LOW); // Turn OFF the red LED
        digitalWrite(GreenLed, HIGH); // Turn on the green LED
        servo.attach(servoPin);
        servo.write(90); // Stop the servo
         
        lcd.setCursor(0, 0);
        lcd.print("   Clear!  "); // Display appropriate message
        lcd.setCursor(0, 1);
        lcd.print("  Safe Environment .  "); // Display environment safe message
      }
      digitalWrite(buzzer, LOW);
      digitalWrite(RedLed, LOW); // Turn OFF the red LED
      digitalWrite(GreenLed, HIGH); // Turn on the green LED
      servo.attach(servoPin);
      servo.write(90); // Stop the servo
      lcd.setCursor(0, 0);
      lcd.print("  Safe Environment . "); // Display appropriate message
      lcd.setCursor(0, 1);
      lcd.print("Environment is safe: " + String(activationDuration) + "ms "); // Display activation duration
      
    }
  } else {
    // Reset activation variables when distance exceeds gas detection range
    activationStartTime = 0;
    activationDuration = 0;
    gasDetected = false;

    digitalWrite(RedLed, LOW);
    digitalWrite(GreenLed, HIGH);
    digitalWrite(buzzer, LOW);
    servo.attach(servoPin);
    servo.write(90); // Stop the servo
    

    lcd.setCursor(0, 0);
    lcd.print("   Clear!  "); // Display appropriate message
    lcd.setCursor(0, 1);
    lcd.print("Environment is safe."); // Display environment safe message
  }
}