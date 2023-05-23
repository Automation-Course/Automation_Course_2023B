
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const int trigPin = 7;               // Ultrasonic sensor trig pin
const int echoPin = 6;               // Ultrasonic sensor echo pin
const int servoPin = 9;              // Servo control pin
const int ledPin = 13;               // LED pin
const int buttonPin = 2;             // Button pin
const int DHTPIN = 3;                // Pin connected to the DHT sensor
const int DHTTYPE = DHT11;           // DHT sensor type
DHT dht(DHTPIN, DHTTYPE);
int cm = 0;
Servo servo;
bool doorOpen = false;
int angle = 0;
int speed = 0;
const int time = 100;
float measureTemperature()
{
  float temperature = dht.readTemperature();
  if (isnan(temperature))
  {
    Serial.println("Failed to read temperature from DHT sensor!");
  }
  else
  {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
  }
  return temperature;
}
float desiredTemperature =24;      // Desired temperature variable
bool flagSerialTemp=false;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);       // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);

  // Reads the echo pin and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void moveServo(Servo& servo, bool& direction, int& angle, int& speed)
{
  unsigned long startTime = millis();  // Record the start time

  if (direction)
  {
    angle += 1;
    speed = 180;
  }
  else
  {
    angle -= 1;
    speed = 0;
  }
  servo.write(speed);
  delay(3000);
  servo.write(90);

  // Check the elapsed time to determine when 1 second has passed
  while (millis() - startTime < 1000)
  {
    // Continue to monitor the time until 1 second has passed
    // You can include additional code or conditions here if needed
    // This loop ensures the servo stays in the desired position for 1 second
  }

  if (angle == 180)
  {
    direction = false;
  }
  if (angle == 0)
  {
    direction = true;
  }
}

void open_door_cmd(bool door_state_open, bool button_state_on, int cm)
{
  // Turn on the LED
  digitalWrite(ledPin, HIGH);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Opening door");

  // Rotate the servo to 180 degrees
  moveServo(servo, doorOpen, angle, speed);

  if (button_state_on)
  {
    lcd.setCursor(0, 1);
    lcd.print("Welcome back");
  }
  delay(1000);

  if (cm <= 100||flagSerialTemp)
  {
    // Measure the temperature
    float temperature = measureTemperature();
    lcd.setCursor(0, 0);
    lcd.clear();
    lcd.print("Temp: ");
    if(flagSerialTemp)
    {
      lcd.print(desiredTemperature);
    }
    else
    {
      lcd.print(temperature);
    }
    lcd.print("C");

    if (temperature <= 20)
    {
      lcd.setCursor(0, 1);
      lcd.print("Wear a sweatshirt");
    }
  }
}

void close_door_cmd(bool door_state_open)
{
  digitalWrite(ledPin, LOW);
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Closing door");

  // Rotate the servo back to the initial position
  moveServo(servo, doorOpen, angle, speed);
  delay(1000);
  lcd.clear();
}

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);   // Set button pin as input with an internal pull-up resistor

  Wire.begin();                       // Initialize I2C communication
  lcd.begin();                        // Initialize the LCD module
  lcd.backlight();                    // Turn on the backlight

  servo.attach(servoPin);
  servo.write(90); // Move the servo to the starting position (90 degrees)

  moveServo(servo, doorOpen, angle, speed);  // Set the initial position of the servo to closed
  delay(500);                         // Wait for the servo to reach the initial position

  dht.begin();
  Serial.begin(9600);                 // Initialize the serial communication

  while (!Serial)
  {
    ; // Wait for the Serial Monitor to open
  }

  Serial.println("Serial Monitor connected.");
}

void loop()
{
  // Read the state of the button
  int buttonState = digitalRead(buttonPin);

  // Measure the distance
  cm = 0.01723 * readUltrasonicDistance(trigPin, echoPin);

  // Check if an object is within 1-meter range
  if ((cm <= 100 && !doorOpen) || (buttonState == LOW && !doorOpen))
  {
    doorOpen = true;

    if (buttonState == LOW)
    {
      open_door_cmd(doorOpen, true, cm);
    }
    else
    {
      open_door_cmd(doorOpen, false, cm);
    }

    delay(10000);  // Wait for 10 seconds
    doorOpen = false;
    close_door_cmd(doorOpen);
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("Door is closed");
    doorOpen = false;
  }

  // Serial Monitor commands
  if (Serial.available())
  {
    char command = Serial.read();

    if (command == 'i')   // (in) Open the door manually as the user is getting inside the house
    {
      if (!doorOpen)
      {
        doorOpen = true;
        Serial.println("Opening door manually - as the user is getting inside the house");
        open_door_cmd(doorOpen, true, cm);
        delay(10000);  // Wait for 10 seconds
        doorOpen = false;
        close_door_cmd(doorOpen);
      }
    }
    else if (command == 'o')   // (out) Open the door manually as the user is getting outside the house
    {
      if (!doorOpen)
      {
        doorOpen = true;
        Serial.println("Opening door manually - as the user is getting outside the house");
        flagSerialTemp=true;
        open_door_cmd(doorOpen, false, cm);
        delay(10000);  // Wait for 10 seconds
        doorOpen = false;
        close_door_cmd(doorOpen);
        flagSerialTemp=false;
      }
    }
    else if (command == 'c')  // Close the door manually
    {
      if (doorOpen)
      {
        doorOpen = false;
        Serial.println("Closing door manually.");
        close_door_cmd(doorOpen);
      }
      else
      {
        Serial.println("The door is already closed!");
      }
    }
    else if (command == 't')   // (t) Set the desired temperature manually
    {
      Serial.println("Enter the desired temperature:");
      while (!Serial.available())
      {
        // Wait for user input
      }
      flagSerialTemp=true;
      float newTemperature = Serial.parseFloat();

      if (newTemperature >= 0)
      {
        desiredTemperature = newTemperature;
        Serial.print("Desired temperature set to: ");
        Serial.print(desiredTemperature);
        Serial.println(" °C");
      }
      else
      {
        Serial.println("Invalid temperature value!");
      }
      flagSerialTemp=false;
    }
  }
}

