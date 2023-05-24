#include <Servo.h>
#include <LiquidCrystal_I2C.h>
//Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd_1(0x27,16,2);


// constants won't change
const int TRIG_PIN  = 7;  // Arduino pin connected to Ultrasonic Sensor's TRIG pin
const int ECHO_PIN  = 6;  // Arduino pin connected to Ultrasonic Sensor's ECHO pin
const int SERVO_PIN = 9; // Arduino pin connected to Servo Motor's pin
const int DISTANCE_THRESHOLD = 50; // centimeters
int tempSensor = A0 ;
int inputTemp1 ;
double temp=25;
int GreenDoorLight=13;
bool TempValid;
bool DisValid;
Servo servo; // create servo object to control a servo

// variables will change:
float duration_us, distance_cm;

void setup() {
  Serial.begin (9600);       // initialize serial port
  pinMode(TRIG_PIN, OUTPUT); // set arduino pin to output mode
  pinMode(ECHO_PIN, INPUT);  // set arduino pin to input mode
  servo.attach(SERVO_PIN);   // attaches the servo on pin 9 to the servo object
  servo.write(0);
  pinMode(tempSensor, INPUT);
  pinMode(GreenDoorLight,OUTPUT);

    //initialize the LCD
  lcd_1.init();
 
  //turn on the blacklight and print a message
  lcd_1.backlight();
 
  lcd_1.begin(16, 2);




}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(ECHO_PIN, HIGH); // meause distance
  // calculate the distance
  distance_cm = 0.017 * duration_us; // convert to CM

   //Temp
  inputTemp1=analogRead(tempSensor);
  temp = map(((inputTemp1/1024.0)*5-0.5)*100, 0, 1023, -50, 125); // convert to Celcuse 
  Serial.print ("Temperature ");
  Serial.println(temp);
  tempCheck(temp);
  DisCheck(distance_cm);
  if(TempValid==false){
    if(DisValid== false){
      servo.write(0);
      printScreen("Close Door");
      digitalWrite(GreenDoorLight, LOW);
      delay(1000);
    } // rotate servo motor to 90 degree
  }
  else{
     servo.write(90);
     printScreen("Door OK");
     digitalWrite(GreenDoorLight, HIGH);
     delay(1000);
  }
  // print the value to Serial Monitor
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  
 
  
  delay(500);
  
}

void printScreen (String print){ // print function
  lcd_1.clear(); // clear screen

  lcd_1.setCursor(0, 1);
  lcd_1.print(print);
  lcd_1.setBacklight(1);  
 
}

void tempCheck (double temp) // function that checks if the temp is valid
{   
 
   if (temp <= 20) // temp ok
    TempValid= true;
   
   else // temp high
   TempValid= false;
}

void DisCheck (double distance_cm) // function that checks if distanse above 50 cm
{   
 
   if (distance_cm > DISTANCE_THRESHOLD) // THRESHOLD = 50
    TempValid= false;
   
   else
   TempValid= true;
}

