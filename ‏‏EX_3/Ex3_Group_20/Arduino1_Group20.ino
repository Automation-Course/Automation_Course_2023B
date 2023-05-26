#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// pins definition
#define led 13
#define servo_pin 8
#define buzer_pin 7
#define PIR_pin 2

bool motion_indicator;
bool direction = true;
int alarm_timer = 5;
int angle = 0;
int volume = 0;
bool alarm_on = false;	
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
  lcd.init();
	lcd.begin(16, 2);
  lcd.backlight();
  Serial.begin(9600);
	pinMode(led, OUTPUT);
  pinMode(buzer_pin, OUTPUT); 
	pinMode(PIR_pin, INPUT);
	servo.attach(servo_pin);
	digitalWrite(PIR_pin, LOW);
}

void loop()
{
	if(detect_motion() || alarm_on){ // Alarm set when motion detected
    alarm();
    alarm_timer--;
    if(alarm_timer == 0){
      alarm_on = false;
    }
  }
  else{
    no_alarm();
  }
  delay(500);
}

bool detect_motion(){ // PIR sensor detection check input
	if (digitalRead(PIR_pin)==HIGH){ // Movement detected
		Serial.println("PIR - high");
    alarm_on = true; // For the timer variable
		return true;
	}
	else{ // No movement
		Serial.println("PIR - low");
		return false;
	}
}

void blink (bool motion_indicator){ // LEDs blink for the detected movement
	int time =0;
	if (motion_indicator){
		time=100;
    Serial.print("alarm blink");
	}
	else{
		time=1000;
    Serial.print("no alarm blink");

	}
	digitalWrite(led, HIGH); // The blink procedure
	delay(time);
	digitalWrite(led, LOW);
	delay(time);
}

void alarm(){ // Alarm set on
	Serial.print("alarm is on!");
  write_to_lcd(true);
  buzer_dimer();
 	move_servo();
  blink(true);
}

void no_alarm(){ // Alarm set off - normal state of the home
  Serial.print("alarm is off!");
  blink(false);
  noTone(buzer_pin); // Restart buzer
  servo.write(90); // Restart servo
  write_to_lcd(false);
}

void move_servo() { // Servo movement for the alarm on state
  servo.write(10);
  delay(300);
  servo.write(170);
  delay(300);
  servo.write(10);
  delay(300);
  servo.write(170);
  delay(300);
  servo.write(10);
  delay(300);
  servo.write(170);
  delay(300);
  servo.write(90);
  angle = 0;
}

void buzer_dimer(){ // Buzer on for the alarm on state
  if(volume>=300){
    volume=100;
  }
  else{
    volume+=10;
   }
  tone(buzer_pin,volume);
  delay(300);
  Serial.print("Buzer is on - the volume is:" + volume);
}

bool write_to_lcd(bool type){  // LCD display for state
  lcd.clear();
  if(type){ // Alarm on
		lcd.print("   Run  away!   ");
		lcd.setCursor(0,1);
		lcd.print("   Group 20!!   ");
    Serial.print("LCD is on - alarm on diaplay");
	}
	else{ // Alaram off
		lcd.print("  Wellcome  To  ");
    lcd.setCursor(0,1);
		lcd.print("  Smart Home ! ");
    Serial.print("LCD is on - alarm off diaplay");
	}
	return true ;
}