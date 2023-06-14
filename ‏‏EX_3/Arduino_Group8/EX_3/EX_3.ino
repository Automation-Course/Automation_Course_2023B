#include <Adafruit_LiquidCrystal.h>
#include <IRremote.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>


//lcd
LiquidCrystal_I2C lcd_1(0x27, 16, 2);
int portion= 10;
//

int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;  // Create a variable to store the results of IR decoding
int onePress = 0;
long duration;
int distance;
const int trigPin = 12;
const int echoPin = 10;

Servo myservo;
int led = 6;
int led2 = 3;

int pir = 2;
int isOpen = 0;
int feedingAllowed = 1;
unsigned long Feeds = 0;
unsigned long lastFeed = 0;


void setup()
{

  //lcd

  lcd_1.begin(16, 2);
  lcd_1.setBacklight(1);

//
  irrecv.enableIRIn(); // Start the receiver

  pinMode(pir, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);

  myservo.attach(9);
  Serial.begin(9600);
  myservo.write(90); // move the servo motor to position 100 to demonstrate open motion
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

}

void loop(){
      // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  lcd_1.setCursor(0, 0); // Sets the location at which subsequent text written to the LCD will be displayed
  
  int portion =10 - (round(distance)/5);
  if(portion<0){
    portion = 0;
    digitalWrite(led2, HIGH);
    lcd_1.clear();
    lcd_1.print("Food thank empty.Refill"); // Prints string "portion" on the LCD
  }
  else{
    lcd_1.clear();
    lcd_1.print("portion: "); // Prints string "portion" on the LCD
    lcd_1.print(portion); // Prints the distance value from the sensor
    digitalWrite(led2, LOW);
  }


   int val = digitalRead(pir);

    if ( millis() - lastFeed > 20000)
  {

   	   feedingAllowed=1;
       results.value = 0;
       onePress=0;


  }

    if (irrecv.decode(&results)) {
      // Process IR remote button press
      if(&results.value!=0){
        onePress = 1;
        Serial.println("Button pressed!");
        results.value = 0;
      }
      
      irrecv.resume();
    }
  
  
  if ((val == HIGH)&&feedingAllowed==1)
    {
       isOpen=1;
       Serial.println("motion detected!");

    }
  
  
  if ((isOpen==1||onePress == 1)&& feedingAllowed==1){  // If the number 1 button is pressed
    digitalWrite(led, HIGH); // turn on the LED
    myservo.write(180); // move the servo motor to position 100 to demonstrate open motion
    isOpen = 1; // set flag to indicate servo is open
    delay(1000); // wait for 5 seconds
    digitalWrite(led, LOW); // turn off the LED
    myservo.write(0); // move the servo motor back to position 0 to close it
    delay(1000); // wait for 5 seconds
    myservo.write(90); // move the servo motor back to position 0 to close it
    isOpen = 0; // set flag to indicate servo is closed
    onePress = 0; // reset the button press variable
    feedingAllowed=0;
    Feeds++;
    Serial.print("Feeds : ");
    Serial.println(Feeds);
    lastFeed = millis();   
    Serial.print("last Feed : ");
    Serial.println(lastFeed );


  }

  delay(10);
  
  
}
