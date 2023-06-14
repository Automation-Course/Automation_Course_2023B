#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> // pyshical package (lcd)
//#include <Adafruit_LiquidCrystal.h> // simulator package

#define servoPin  9
#define ledPinGreen 2 
#define ledPinYellow  5  
#define ledPinRed 11
#define PhotoresistorPin  A0 

// Servo
Servo servo;
int ServoSpeed =90;
bool DirectionLefttToOpened=true;
bool DirectionAgainst90=true;

// Button
int pushButton = 4; //Variable for storing Push Button Pin Configuration
int switchStatus = 0; //Initializing variable value of switchStatus to 0 

// LCD
//Adafruit_LiquidCrystal lcd(0); // simulator package
LiquidCrystal_I2C lcd(0X27,16,2);// pyshical package (lcd)

//photoresistor
int PhotoresistorValue=0; // the analog reading from the sensor divider

bool ShutterInMove = false;
bool shutterIsClose = false;
 
void setup() 
{
	
	Serial.begin(9600); 	
	servo.attach(servoPin);

/////// simulator package //////	
    //lcd.begin(16, 2);
    //lcd.setBacklight(1);
  
/////// pyshical package //////
	lcd.init();// initialize the LCD
	//Turn on the blacklight and print a message.
	lcd.backlight();
  
	lcd.print("Hello, Orit!");
	delay(900);
	
	//Setting leds as output
	pinMode(ledPinRed, OUTPUT); 
	pinMode(ledPinGreen, OUTPUT); 
	pinMode(ledPinYellow ,OUTPUT);
	
	//Setting inputs
	pinMode(pushButton , INPUT); 
	pinMode(PhotoresistorPin,INPUT);
}

void loop() 
{
	lcd.clear(); 
	PhotoresistorValue = analogRead(PhotoresistorPin); // reads the light and translate it to number
   
  // Check if the shutters are open and need to be close
	if ((PhotoresistorValue <403)and(ServoSpeed == 90)and(!shutterIsClose)) 
    {
      OpenShutter();
    }
	//Check if the shutters are closed and need to be open
	if ((PhotoresistorValue>403) and (ServoSpeed == 90)and (shutterIsClose)) 
	{
      CloseShutter();
	}
	
	getButton();
	if(ShutterInMove)
		moveServo();
	// prints the ServoSpeed and photoresistor value to serial
  PrintLDRValue();
}  

void PrintLDRValue(){
  	Serial.print("LDR Value: ");
   	Serial.println(PhotoresistorValue);      
}

void OpenShutter(){
    blinkingYellow();
	  lcd.print("Open shutter");
    Serial.print("Open shutter. LDR Value: ");
   	Serial.println(PhotoresistorValue); 
    delay(100);
}
// blinking lights yellow 
void blinkingYellow(){
	digitalWrite(ledPinYellow,HIGH);
	delay(100);
	digitalWrite(ledPinYellow,LOW);
	delay(100);	
}	

void CloseShutter(){
     blinkingRed();
	 	 lcd.print("Close shutter");
     Serial.print("Close shutter. LDR Value: ");
   	 Serial.println(PhotoresistorValue); 
     delay(100);
}
A
// blinking lights red
void blinkingRed(){
  	digitalWrite(ledPinRed,HIGH);
  	delay(100);
  	digitalWrite(ledPinRed,LOW);
  	delay(100);	
}


// define what happens after we press the button
void getButton()
{
// when button is pressed action will occur only when change is needed  
  if(((PhotoresistorValue<403)and(ServoSpeed == 90)and(!shutterIsClose))or((PhotoresistorValue>403) and (ServoSpeed == 90)and (shutterIsClose)))
  {
  //gets the reading from the button and updates the variable
    switchStatus = digitalRead(pushButton); 
    UpdatesVariable();     
  }
}

void UpdatesVariable(){
    if(switchStatus == LOW) //If the button is not pressed, the LED will not light up
    {
       digitalWrite(ledPinGreen, LOW);
    }
    else
    {
    digitalWrite(ledPinGreen, HIGH); // if the the button is pressed, the light is on
	     ShutterInMove = true; 
    }
}

void moveServo()
{
    //increase the ServoSpeed
	if (DirectionAgainst90)
    {
      IncreaseServoSpeed();
    }
    //lower the ServoSpeed
  else 
    {
    LowerServoSpeed();
    }     	
	//shutters are closed 
	if((ServoSpeed==90)and (DirectionLefttToOpened))
	{
      ShuttersOpened();		
	}  
    //shutters are open
	else if((ServoSpeed==90)and (!DirectionLefttToOpened))
	{
      ShuttersClosed();      
    }
    servo.write(ServoSpeed);
}

// increase the ServoSpeed
void IncreaseServoSpeed(){  
     // increase the ServoSpeed when need close the shutter
      if(DirectionLefttToOpened)
      {
        if(ServoSpeed<150)
        {
		   ServoSpeed +=1;
        }
      	else
       	{
           DirectionAgainst90=false;
       	}
      }
      // increase the ServoSpeed when need open the shutter
      else
      {
        if(ServoSpeed>30)
        {
          ServoSpeed -=1;
        }
        else
       	{
        	DirectionAgainst90=false;
       	}
      }      	
}

void LowerServoSpeed(){
   // lower the ServoSpeed when need close the shutter
      if(DirectionLefttToOpened)
      {
        if(ServoSpeed>90)
        {
            ServoSpeed -=1;
        }
       	else
       	{
        	DirectionAgainst90=true;
       	}
      }
      //ower the ServoSpeed when need open the shutter
      else
      {
         if(ServoSpeed<90)
         {
            ServoSpeed +=1;
         }
         else
       	 {
        	DirectionAgainst90=true;
       	 }
      }  
}

void ShuttersOpened(){
      DirectionLefttToOpened = false;
      DirectionAgainst90=true;
	    ShutterInMove=false; 
   	  shutterIsClose = true;
      lcd.print("Shutter open");
      digitalWrite(ledPinGreen, LOW);
      delay(500);
}

void ShuttersClosed(){
      DirectionLefttToOpened = true;
      DirectionAgainst90=true;
	    shutterIsClose = false;
	    ShutterInMove =false;
      lcd.print("shutter closed");
      digitalWrite(ledPinGreen, LOW);
      delay(500);     
}