•	// Libraries and inits
•	#include <LiquidCrystal_I2C.h>;
•	#include <Servo.h>;
•	LiquidCrystal_I2C lcd(0x27, 16, 2);
•	Servo myservo;
•	
•	// Variables
•	#define pirSensor 2
•	#define led 5
•	#define piezo 3
•	#define servoPin 9
•	#define buttonPin 4
•	#define onPin2 7
•	#define trigPin 12
•	#define echoPin 13
•	long distance = 0;
•	long duration = 0;
•	int buttonState = 0;
•	int onButton = 0;
•	bool alarmActive = false;
•	int servoPos = 0;
•	int angle = 95;
•	int speed = 0;
•	bool shutterCloses = false;
•	bool Direction = true;
•	bool pushButtom = false;
•	bool systemOn=false;
•	
•	void setup() {
•	  lcd.begin(16, 2);
•	  
•	  Serial.begin(9600);
•	
•	  // Set the LED pin as an output
•	  pinMode(led, OUTPUT);
•	
•	  // Set the piezo buzzer pin as an output
•	  pinMode(piezo, OUTPUT);
•	
•	  // Set the servo pin as an output
•	  myservo.attach(servoPin);
•	
•	  // Set the ultrasonic 
•	  pinMode(trigPin, OUTPUT);
•	  pinMode(echoPin, INPUT);
•	
•	  // Set the push button pin as an input
•	  pinMode(buttonPin, INPUT_PULLUP);
•	  
•	   // Set the push button pin as an input
•	  pinMode(onPin2, INPUT_PULLUP);
•	
•	  // Print the initial message on the LCD screen
•	  lcd.init();
•	  lcd.backlight();
•	  lcd.print("");
•	}
•	
•	void loop() {
•	  
•	  checkSystemState();
•	  if (systemOn==true){ 
•	    checkButtonState();
•	  checkUltraSonicSensor();
•	   if (pushButtom==false)
•	   {
•	     keepAlarmActive();
•	   }
•	    delay(50); // add a small delay to prevent flickering of the LCD screen
•	    checkButtonState();
•	    if (pushButtom==true)
•	      {   
•	      turnOffAlarm();
•	      delay(1000);
•	      }
•	      Serial.println(1);
•	    }
•	}
•	
•	void checkSystemState() {
•	  // Read the state of the push button
•	  onButton = digitalRead(onPin2);
•	  
•	  // If the push button is pressed, turn off the LED, piezo, and servo motor
•	  if (onButton == LOW) 
•	  { 
•	    if (systemOn==false){
•	      systemOn=true;
•	      lcd.clear();
•	      lcd.print("Thief Detection");
•	      Serial.println("System is on");
•	      delay(5000);
•	    }
•	    else {
•	      systemOn=false;
•	      lcd.clear();
•	      lcd.print("System Off");
•	      digitalWrite(led, LOW);
•	      Serial.println("System is Off");
•	      delay(5000);
•	    }
•	  }
•	}
•	void checkButtonState() {
•	  // Read the state of the push button
•	  buttonState = digitalRead(buttonPin);
•	
•	  // If the push button is pressed, turn off the LED, piezo, and servo motor
•	  if (buttonState == LOW && alarmActive) {
•	    pushButtom=true;
•	  }
•	}
•	
•	void turnOffAlarm() {
•	  digitalWrite(led, LOW);
•	  noTone(piezo);
•	  alarmActive = false;
•	  shutterCloses = false; 
•	  pushButtom=true;
•	  lcd.setCursor(0, 1);
•	  lcd.print("Area Clear       ");
•	  Serial.println("turn off the alarm");
•	  openShutters();
•	}
•	
•	void checkUltraSonicSensor() {
•	  // If the PIR sensor detects motion and the alarm is not already active, activate the alarm and servo motor
•	 digitalWrite(trigPin,LOW);
•	 delayMicroseconds(2);
•	 digitalWrite(trigPin,HIGH);
•	 delayMicroseconds(10);
•	 digitalWrite(trigPin,LOW);
•	 duration = pulseIn(echoPin,HIGH);
•	 distance = duration*0.034/2;
•	  if (distance<10 && !alarmActive && pushButtom==false) {
•	    activateAlarm();
•	  }
•	}
•	
•	void activateAlarm() {
•	  // Turn on the LED
•	  digitalWrite(led, HIGH);
•	
•	  // Print "Motion Detected" on the LCD screen
•	  lcd.setCursor(0, 1);
•	  Serial.println("Active the alarm");
•	  lcd.print("Motion Detected");
•	
•	  // Activate the piezo buzzer
•	  tone(piezo, 1000, 5000);
•	
•	  // Move the servo motor to simulate the closing of the blinds
•	  alarmActive = true;
•	  activateShutters();
•	}
•	
•	void keepAlarmActive() {
•	  // If the alarm is active, keep the piezo buzzer on
•	  if (alarmActive) {
•	    shutterCloses = true;
•	    tone(piezo, 1000, 500);
•	    
•	  }
•	}
•	
•	void activateShutters(){  
•	    speed=180;
•	   myservo.write(speed);
•	   delay(3000);
•	   speed=90;
•	   myservo.write(speed);
•	  }
•	
•	void openShutters(){
•	    speed = 0;  
•	   myservo.write(speed);
•	   delay(3000);
•	   speed=90;
•	   myservo.write(speed);
•	   pushButtom=false;
•	  }

