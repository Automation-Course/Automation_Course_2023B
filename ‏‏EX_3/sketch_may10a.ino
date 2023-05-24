#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define servoPin 11

Servo servo;
// constant and variables setup 
int Button = 0;
bool Gate = false;
int speed = 90;
const int TrigerPin = 2; 
const int echoPin = 5; 
long duration,distance;
// screen setup to 16 char and 2 rows
LiquidCrystal_I2C lcd(0x27,16,2);
void setup()
{
Serial.begin(9600); 
//setup of screen
lcd.init();
lcd.backlight(); 
servo.attach(3);
  pinMode (3,INPUT);
  pinMode (10,INPUT);
  pinMode (4, INPUT);
}
void loop() {
pinMode(TrigerPin, OUTPUT); digitalWrite(TrigerPin, LOW); delayMicroseconds(2); digitalWrite(TrigerPin, HIGH); delayMicroseconds(10); digitalWrite(TrigerPin, LOW); pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
distance = microsecondsTodistance(duration); 
//screens show up according if we are close enough and the red light turns when we are to far
if ( distance < 13.4)
{
Screen2(); digitalWrite(10,LOW); //red light truns off when we you get closer
}
else
{
Screen1(); digitalWrite(10,HIGH); //red light turns on when you are to far
}
Button = digitalRead(7);
if ((Button == 1)&&(Distance_Sensor()<=13.4))//if the button was pressed and we are in the right range
Gate = true;
//if the gate isnt moving 
if ((Gate)&&(speed=90))
{
servo.write(80); //opening
delay(2000); 
//waits until the car enters
servo.write(90);
delay(5000);
flichers();
//WARNING screen when gate is closing
Screen3();
servo.write(100);//closing
delay(2000);
Gate = false; 
}
else
{  
servo.write(90);
Gate = false;
Button=0;
} 
}
//converting time to cm
long microsecondsTodistance(long microseconds) {
      return microseconds / 29 / 2;
}    
//disstance sensor setup 
long Distance_Sensor()
{
long duration,distance; 
pinMode(TrigerPin, OUTPUT); 
digitalWrite(TrigerPin, LOW); 
delayMicroseconds(2); 
digitalWrite(TrigerPin, HIGH); 
delayMicroseconds(10); 
digitalWrite(TrigerPin, LOW); 
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH); 
distance = microsecondsTodistance(duration); 
return distance;
}
//screens functions
void Screen1()
{  
lcd.setCursor(2,0);
 lcd.print("PLEASE COME   ");
 lcd.setCursor(2,1);
 lcd.print("   CLOSER          ");
 }
 void Screen2()
 {
 lcd.setCursor(2,0);
 lcd.print("PLEASE PRESS   ");
 lcd.setCursor(0,1);
 lcd.print("    THE BUTTON ");
}
 void Screen3()
 {
 lcd.setCursor(2,0);
 lcd.print(" CLOSING GATE");
 lcd.setCursor(0,1);
 lcd.print("  STAY AWAY       ");
}
void flichers(){
digitalWrite(10,HIGH); //red light flichers when the gate is about to close
delay(500); 
digitalWrite(10,LOW); 
delay(500); 
digitalWrite(10,HIGH);
delay(500); 
digitalWrite(10,LOW); 
delay(500); 
digitalWrite(10,HIGH); 
delay(500); 
digitalWrite(10,LOW); 
delay(500); 
digitalWrite(10,HIGH); 
}