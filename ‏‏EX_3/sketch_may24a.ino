//LCD
//bakar
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);


//SERVO
#include <Servo.h>
Servo servo;
int angle = 0;
int speed = 0;
bool direction = true;  //true=left, false=right
bool moveGate = false;

//#include <Ultrasonic.h>


#define led 1
//#define PIR_pin 2 //not needed
//#define distance_pin 8
#define servo_pin 9
#define trigPin 3
#define echoPin 4

long duration;
long dist;
long distanceTime;


const int buttonPin = 2;
bool button_pressed;
int state = 0;

void setup() {
  

  //lcd.begin(16,2); //simulation
  lcd.init();                  //bakar
  lcd.backlight();             //bakar
  lcd.print("Hello Maya :)");  //simulation+bakar
  pinMode(buttonPin, INPUT);
  pinMode(led, OUTPUT);
  servo.attach(servo_pin);
  servo.write(90);
  Serial.begin(9600);
}

void loop() {
  calDistance();
  if (dist <= 20) {
    turnonGreenLight();
    showDisplayFirstMessage();  //show welcome message
    button_pressed = checkButton();
    if (button_pressed) {
      Serial.print("button status ");
      Serial.println(button_pressed);
      moveGate = true;
      Rotate();
    }
  } else {
    turnoffGreenLight();
    lcd.setCursor(0, 1);
    lcd.clear();
    lcd.println("Get closer");

  }
}

bool checkButton() {
  int stateButton = digitalRead(buttonPin);
  if (digitalRead(buttonPin) == 1) {
    lcd.clear();
    lcd.println("Open Gate");
    return true;
  } else {
    lcd.clear();
    lcd.println("Not pressed");
    return false;
  }
}

void turnonGreenLight() {
  digitalWrite(led, HIGH);
  //delay(500); // Wait for 1000 millisecond(s)
}

void turnoffGreenLight() {
  digitalWrite(led, LOW);
  //delay(500); // Wait for 1000 millisecond(s)
}

void calDistance() {
  //distanceTime=millis();
  pinMode(trigPin, OUTPUT);
  //digitalWrite(distance_pin, LOW);
  //delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  //delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  //pinMode(distance_pin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  dist = duration / 29 / 2;
}

void showDisplayFirstMessage() {
  lcd.setCursor(0, 1);
  lcd.print("press to open");  //open the gate
  delay(500);
}


void Rotate() {
  if (moveGate && button_pressed) {
    if (direction && angle<10){ //open gate
    angle+=1;
    speed=180;
    lcd.clear();
    lcd.println("Opening");
    }else{ //close gate
    angle-=1;
    speed=0;
    lcd.clear();
    lcd.println("Closing");
    }
    Serial.print("angle ");
    Serial.println(angle);    // the raw analog reading
    servo.write(speed);
  }
  if (angle==10) {
    direction=false;
  }
  if (angle==0) {
    direction=true;
    moveGate=false;
    servo.write(90);
    button_pressed= false;
  }
}

/*  if (direction && moveGate && angle < 15) {  
      angle += 1;
      speed = 180;
      lcd.clear();
      lcd.println("Opening");
      Serial.print("angle = ");
      Serial.println(angle);
    }else {
    angle -= 1;
    speed = 0;
    lcd.clear();
    lcd.println("Closing");
    Serial.print("angle = ");
    Serial.println(angle);
    }
  servo.write(speed);
  //if (angle = 0) {
  //  direction = true;
  //  servo.write(90);
  //  moveGate = false; //finish open and close stage
  //}
  if (angle = 15) {
    direction = true;
    servo.write(90);
  }
}

  if ((direction == true) and (angle<180) and (moveGate)){ //gate not fully close and want to open
   angle +=90;
    servo.write(angle);
   lcd.clear();
   lcd.print("wait to open");
  }
  if ((direction == false) and (angle<180) and (angle!=0)){ //gate not fully close and want to close
   angle -=90;
    servo.write(angle);
   lcd.clear();
   lcd.print("wait to close");
  }
  if(angle == 180){ //fully open 
    lcd.clear();
    lcd.print("Maya, please enter");
    direction = false;
	delay(1000);
    angle -=90; //prevent from inifity loop 
    servo.write(angle);

  }
  if(angle == 0){ // //fully close
    direction = true;
    moveGate = false;
    button_pressed = false;
  }
  //servo.write(angle);
  delay(1000);
}*/