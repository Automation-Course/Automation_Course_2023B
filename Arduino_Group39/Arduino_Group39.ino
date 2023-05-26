#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define led 4
#define servo_pin 12
#define buzer_pin 9
#define PIR_pin 2

//bool motion_sensor;
bool direction = true;
int angle = 0;
int volume = 0;
bool lcd_safe = false;
bool lcd_alarm = false;
LiquidCrystal_I2C lcd_1(0x27, 16, 2);
Servo servo;
int timer = 30;

void setup()
{
  lcd_1.init();
  lcd_1.backlight();
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(buzer_pin, OUTPUT);
  pinMode(PIR_pin, INPUT);
  servo.attach(servo_pin);
  digitalWrite(PIR_pin, LOW);
  timer = 30;
  //lcd.begin();

}

void loop()
{
  //lcd_1.print("Leave My House!");
      if (detect_motion()){
          move_servo();
          buzzer_dimmer();
          blink(true);
          alarm();
      } 
      else{
        no_alarm();
        blink(false);
        servo.write(90);
        if (!lcd_safe)
         {
         lcd_safe = write_to_lcd('O', lcd_safe);
        }
         lcd_alarm = false;
        noTone(buzer_pin);
      }   
}

void blink(bool motion_sensor)
{
  int speed = 0;
  if (motion_sensor)
  {
    speed = 200;
  }
  else
  {
    speed = 1000;
  }
  digitalWrite(led, HIGH); // set the led on
  delay(speed);             // wait for a second
  digitalWrite(led, LOW);  // turn the LED off
  delay(speed);            // wait for a second
}

bool detect_motion()
{
  if (digitalRead(PIR_pin) == HIGH)
  {
    //serial.println("detect movment");
    return true;
  }
  else
  {
  //serial.println("no movement");    
    return false;
  }
}
void alarm()
{
  if (!lcd_alarm)
  {
    lcd_alarm = write_to_lcd('A', lcd_alarm);
  }
  lcd_safe = false;
}

void no_alarm()
{ 
  servo.write(90);
  if (!lcd_safe)
  {
    lcd_safe = write_to_lcd('O', lcd_safe);
  }
  lcd_alarm = false;
  //digitalWrite(buzer_pin, LOW); // Turn off the active buzzer immediately
}

void move_servo()
{
  if (direction)
  {
    angle += 60;
  }
  else
  {
    angle -= 60;
  }
  servo.write(angle);
  if (angle == 180)
  {
    direction = false;
  }
  if (angle == 0)
  {
    direction = true;
  }
}

void buzzer_dimmer()
{
  volume = 300;
  tone(buzer_pin, volume);
  Serial.print(volume);
}

bool write_to_lcd(char type, bool type_end)
{
  if (type == 'A')
  {
    lcd_1.clear();
    lcd_1.print("Leave My House!");
    lcd_1.setCursor(0,1);
    lcd_1.print("I will call 911!");
  }
  if (type == 'O')
  {
    lcd_1.clear();
    lcd_1.print("Safe Home :)");
  }
  type_end = true;
  return type_end;
}