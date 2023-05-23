#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>

#define servoPin  9
#define ONE_WIRE_BUS 6 

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int s_temp = 6;
int s_gas = A1;
int smoke_led = 5;
int cooling_led = 4;
int heating_led = 3;
int speed = 180;
LiquidCrystal_I2C lcd_1(0x27, 16, 2);  //init LCD

bool coolingOn=false;
bool heatingOn=false;

Servo myServo;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd_1.init();
  pinMode(s_temp, INPUT);
  pinMode(s_gas, INPUT);
  pinMode(smoke_led, OUTPUT);
  pinMode(cooling_led, OUTPUT);
  pinMode(heating_led, OUTPUT);
  myServo.attach(9);
  myServo.write(0);
  lcd_1.backlight();
}

void loop() {  
  int gasLevel = analogRead(s_gas);
  if (gasLevel < 200) { // no gas detected -> control AC by temp
    digitalWrite(smoke_led, LOW);
    if (getTemp()>24) 
      cooling();
    else if (getTemp()<22) 
      heating();
    else  
      perfectTemp();
  }
  else{ // gas detected!!
    turnOffAC();
    lcd_1.clear();
    lcd_1.print("GAS DETECTED!!!!"); 
    digitalWrite(smoke_led, HIGH);
  }
}

void cooling() {
  heatingOn = false;
  coolingOn = true;
  digitalWrite(heating_led, LOW);
  digitalWrite(cooling_led, HIGH);
  lcd_1.clear();
  lcd_1.setCursor(0,0);
  lcd_1.print("AC Cooling ");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Temp: " + String(getTemp()) + "C");
  myServo.write(speed); //turn on myServo
}

void heating() {
  coolingOn = false;
  heatingOn = true;
  digitalWrite(cooling_led, LOW);
  digitalWrite(heating_led, HIGH);
  lcd_1.clear();
  lcd_1.setCursor(0,0);
  lcd_1.print("AC heating ");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Temp: " + String(getTemp()) + "C");
  myServo.write(speed); //turn on myServo 
}

void perfectTemp() {
  if (coolingOn || heatingOn) {
    lcd_1.clear();
    lcd_1.setCursor(0,0);
    lcd_1.print("Perfect temp :) ");
  } 
  turnOffAC();
}

void turnOffAC(){
  coolingOn = false;
  heatingOn = false;
  digitalWrite(heating_led, LOW);
  digitalWrite(cooling_led, LOW);
  myServo.write(0); //turn off myServo
}

float getTemp() { 
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
    Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println("°C");
  return temperatureC;
}