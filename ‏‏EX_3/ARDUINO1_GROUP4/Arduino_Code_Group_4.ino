// library
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
Servo servo; //Create a servo 

//Create LCD
LiquidCrystal_I2C lcd(0x27,16,2); //set the LCD address to 0x27 for a 16 chars and 2 line display
//create variables:
//Buzzer:
int buzzer = 8;
//Servo:
int servoPin = 3;
int angle = 0; 
bool direction = true;
//LED:
bool isLedOff = true;
int ledRed = 2;
//UltraSonic:
int soundWaveOutPin = 10;
int soundWaveInPin = 9;
//Distance:
long distance, duration;

void setup() {
lcd.init(); //initialization of the LCD screen
//Print a message
lcd.backlight();
//Blinking block cursor
lcd.blink_on();
//define:
pinMode(soundWaveOutPin,OUTPUT);
pinMode(soundWaveInPin,INPUT);
pinMode(buzzer, OUTPUT);
servo.attach(servoPin);
Serial.begin(9600);
}

void loop() {
ultraSonic();
calcDist();
if(distance < 70){
burglarArrive(); //burglar is nearby
}
else{
normalMode(); //return to normal mode
}
}

void ultraSonic() {
digitalWrite(soundWaveOutPin, LOW);
delayMicroseconds(2);
//Sets the soundWaveOutPin HIGH 
digitalWrite(soundWaveOutPin, HIGH);
delayMicroseconds(10); //10 μs
digitalWrite(soundWaveOutPin, LOW);
}

void calcDist() {
//Reads the soundWaveInPin
duration = pulseIn(soundWaveInPin, HIGH);
//Calculate the distance
distance = duration * 0.034 / 2; //sound wave' speed divided by 2 (back and forth)
}

void burglarArrive() {

// Displays the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.print(distance);
Serial.println(" cm");
lcd.clear();
lcd.print("Burglar Alert!"); //print the message to the LCD screen
lcd.setCursor(0, 1); //move to the next line
lcd.print("distance :"); 
lcd.print(distance);
lcd.print(" cm");
blink(ledRed);
buzz(buzzer);
Servo();
delay(1000);
}

void normalMode() {
tone(buzzer, 40000); //stop sound
servo.write(90); //no motion
digitalWrite(ledRed, LOW); //turn the led off
lcd.clear();
}

void blink(int led) {
if (isLedOff){
digitalWrite(led, HIGH); //turn the led on
isLedOff = false;
}else{
digitalWrite(led, LOW); //turn the led off
isLedOff = true;
}
}
void buzz(int Buzzer) {
tone(Buzzer, 800); //Send 0.8KHz sound signal
}

void Servo() { //Servo is on
angle = 180;
servo.write(angle);
delay(1000);
servo.write(90); //no motion
if(angle == 0)
direction = true;
if(angle == 180)
direction = false;
}