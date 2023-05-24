#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Pin definitions
#define TRIGGER_PIN 2
#define ECHO_PIN 3
#define PIEZO_PIN 9
#define SERVO_PIN 10
#define RED_LED_PIN 11
#define GREEN_LED_PIN 12
Servo servo;

// Initialize LCD object
LiquidCrystal_I2C lcd(0x27, 16, 2);

void initializePins() {
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIEZO_PIN, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
}

void initializeLCD() {
  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Win dodo System");
  delay(2000);
}

void displayDistanceWarning() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("No entry ");
  lcd.setCursor(0, 1);
  lcd.print("you are too close");
}

void activateWarningComponents() {
  digitalWrite(RED_LED_PIN, HIGH);
  tone(PIEZO_PIN, 1000, 100); 
}

void startTemperatureRegulation() {
  digitalWrite(GREEN_LED_PIN, LOW);
  servo.write(180);
  // delay(5000);
}

void stopTemperatureRegulation() {
  servo.write(90); // Set servo to neutral position
}

void displayAreaCleanMessage() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Area Clean");
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, LOW);
}

void stopServoIfGreenLightOn() {
  if (digitalRead(GREEN_LED_PIN) == HIGH) {
    servo.write(90); // Set servo to neutral position
  }
}

void setup() {
  initializePins();
  initializeLCD();
}

void loop() {
  // Read distance from ultrasonic sensor
  long duration, distance;
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration * 0.034 / 2;

  // Check if distance is within range
  if (distance < 15) { 
    displayDistanceWarning();
    activateWarningComponents();
    startTemperatureRegulation();

    if (digitalRead(GREEN_LED_PIN) == HIGH) {
      stopTemperatureRegulation();
    }
  }
  else {
    displayAreaCleanMessage();
    stopServoIfGreenLightOn();
  }
}