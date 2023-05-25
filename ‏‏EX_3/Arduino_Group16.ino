// C++ code
#include <Wire.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27,16,2); // מסך של הגדרה LCD

//Set the servo
Servo servo;

//הגדרה של הנורה
#define ledPin 11
int ledbrightness;

//הגדרה של חיישן האור
#define photoresistorePin  A1
int photoresistoreValue =  0;

//הגדרה של חיישן טמפרטורה
#define ONE_WIRE_BUS 4
double tempValue;
int maxTemp = 27;
int minTemp = 25;

//הגדרה של מנוע הסרבו 
#define servoPin  9
int speed = 0;

//הגדרה של החיישן טמפרטורה
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup()
{
  //אתחול מסך הLCD
lcd.init();

//הדלקת האור והדפסת ההודעה
lcd.backlight();
Serial.begin(9600);

//הגדרת כניסות ויציאות
pinMode(ledPin,OUTPUT);
pinMode(photoresistorePin,INPUT);

printLCD("WELCOME HOME!");

//אתחול הסרבו
servo.attach(servoPin);

//אתחול סנסור הטמפרטורה
sensors.begin();
}

void loop(){

//דגימת ערכים מחיישן האור
  photoresistoreValue = analogRead(photoresistorePin); 
  //התאמת הערכים בין חיישן האור לנורה
	// 80 מציין שהחיישן קולט כמות גדולה של אור
  //1022 מציין שהחיישן לא קולט אור 
  ledbrightness = map(photoresistoreValue, 80, 1022, 0, 255);
  Serial.print("The photoresistore value: ");
  Serial.println(photoresistoreValue );
  //תנאי להדלקה/כיבוי הנורה
  if (photoresistoreValue > 900){
    	analogWrite(ledPin, ledbrightness);
  }
  else{
  //החיישן מקבל מספיק אור - הנורה לא צריכה להדלק
	analogWrite(ledPin, 0);
	delay(100);
  }

//חיישן טמפרטורה
sensors.requestTemperatures();
Serial.print("The temp is:");
Serial.println(sensors.getTempCByIndex(0));
tempValue = sensors.getTempCByIndex(0);
checkTheTemp(tempValue);
}

//פונקציה שבודקת את ערך הטמפרטורה
 void checkTheTemp (double tempValue) {
   
   if (tempValue >= maxTemp){
     printLCD(" TOO HOT!!!!!"); 
     delay(3000);
     //פונקציה שמפעילה את מנוע הסרבו 
     StartToCool();
   }
   
   if (tempValue <= minTemp){
     printLCD("STOP COOL DOWN");
     delay(3000);
     //פונקציה שעוצרת את מנוע הסרבו
     StopToCoolDown();
   }
 }

void StartToCool(){
  lcd.clear();
  printLCD("COOLING DOWN");
  servo.write(180);
      
}

void StopToCoolDown(){
  lcd.clear();
  printLCD("TEMP IS OK");
  //מהירות 90 עוצרת את הסרבו
  servo.write(90);
}


//פונקציית הדפסה לLCD
void printLCD (String print){
 lcd.setCursor(0, 1);
 lcd.print(print);
 lcd.setBacklight(1);
}