#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

//-------------------------constants and variables-------------------------------------------

// ----------------LCD 
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ----------------LED- PIEZO
const int led_pin = 2; 
const int buzzer_pin = 3; 

// ---------------- PIR
const int pir_pin = 6; 
int warm_up_time = 60;                // sensor warm up time sensor 
unsigned long last_motion_time = 0;  // track last detected motion time
unsigned long pause = 5000;         // time the sensor become low before assuming motion stop (milliseconds)

// ----------------Servo
const int lock_pin = 5; 
Servo servoMotor;

// -----------------RFID
const int ss_pin = 10;
const int rst_pin = 9;
MFRC522 mfrc522(ss_pin, rst_pin);


// RFID tag IDs -keys
const String master_key = "DA6FFCB0";


// Time for waiting before displaying "No one is home" message
const unsigned long wait_time = 8000;

// indicator for system status
unsigned long visitor_timer = 0;
bool is_locked = true; 


//----------------setup-------------------------------------------

void setup() {
  Serial.begin(9600);
  SPI.begin();
  Serial.print("system warm up");
  Serial.println();

// ----------------LCD  
  LCDSetUp();

// ----------------LED- buzzer
  pinMode(led_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);

// ---------------- PIR
  pinMode(pir_pin, INPUT);
  digitalWrite(pir_pin, LOW);
  PIRWarmUp();//give the sensor some time to warm up

// -----------------RFID
  mfrc522.PCD_Init();
  
// ----------------Servo
 servoMotor.attach(lock_pin);

}

//----------------main loop-------------------------------------------
void loop() {
  //Serial.println();
  Serial.println("new loop begin"); //to helps us track 

  LCD_WelcomeARIS();
  LCD_ScanCard();

  
  bool approved_key = false; // Initialize approved flag


  // RFID is detected
  if (checkRFID(approved_key)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Scanning");
    delay(1000);

    // Case 1: Authorized Access - RFID key is a match and door is closed
    if (approved_key) {
      if (is_locked) { // check the door is closed before opening
        Serial.println("Case 1: Authorized Access"); 
        AccessGranted();
      } 
      else {
        lockDoor(); // close the door if its was open.
        lcd.print("Door is locked");
        delay(5000);
      }
    }
    // Case 2: Access is denied - RFID key is not a match 
    else {
      Serial.println("Case 2: Access is denied"); 
      AccessDenied();
    }
  }
  // Case 3: No RFID detected, PIR Movement detected, check for visitor option
  // waiting for the owner to open the door or get a "No response" message after a period of time 
  else {
    if (checkVisitor()) {
      Serial.println("Case 3: Visitor is detected");
      VisitorDetected();
      bool is_owner_arrived = false;

      while ((millis() - visitor_timer) < wait_time) {
        // Check for the homeowner's arrival
        if (checkRFID(approved_key)) {
          if (approved_key) {
            is_owner_arrived = true;
            break;
          }
        }
      }
      if (is_owner_arrived) {
        Serial.println("Case 3.1: Owner open the door");
        ownerOpened();
      }
      else {
        Serial.println("Case 3.2:no Response");
        noResponse();
      }
    }
  }
}


//----------------Function Definitions------------------------------------

//----------------RFID operation---------------------

// Function to check RFID tag
bool checkRFID(bool& approved_key) {
  // If a new PICC placed to RFID reader and since a PICC placed
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    String rfid = getRFIDTag();
    Serial.println("-------RFID: ");
    Serial.println(rfid);
    if (rfid == master_key) {
      approved_key = true;
      return true;
    }
    else {
      approved_key = false;
      return true;
    }
  }
  return false;
}

// Function to read RFID tag
String getRFIDTag() {
  String rfid = "";
  // The MIFARE PICCs that we use have 4 byte UID
  for (uint8_t i = 0; i < mfrc522.uid.size; i++) {
    // Adds the 4 bytes in a single String variable
    rfid.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  rfid.toUpperCase();
  mfrc522.PICC_HaltA();// Stop reading
  return rfid;
}

//----------------PIR operation-------------------------------------------

bool checkVisitor() {
  if (digitalRead(pir_pin) == HIGH ) {
    // If motion detected- update the last detected motion time
    last_motion_time = millis();
    return true;
  }
  else {
    // If no motion detected for the specified pause time, reset the motion status
    if ((millis() - last_motion_time) > pause) {
      return false;
    }
    return true;
  }
}

//----------------alarm operation-------------------------------------------

void activateAlarm(int duration) {
  digitalWrite(led_pin, HIGH); 
  tone(buzzer_pin, 5000); 
  delay(duration); 
}

void turnOffAlarm(){
  digitalWrite(led_pin, LOW);
  noTone(buzzer_pin);
}

//----------------door operation-------------------------------------------

void unlockDoor() {
  servoMotor.write(180);
  delay(2000); 
  servoMotor.write(90); 
  is_locked = false;
  Serial.println("Unlocking door");

  // Buzzer when the door opens
  tone(buzzer_pin, 2000, 200);
  delay(200);
  noTone(buzzer_pin);
}

void lockDoor() {
  servoMotor.write(0); 
  delay(2000); 
  servoMotor.write(90); 
  is_locked = true;
  Serial.println("Locking door");
}

//---------------- LCD operation ------------------------

void LCD_WelcomeARIS() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Welcome to ARIS");
  lcd.setCursor(0, 1);
  lcd.print("SmartLock System");
  delay(2000);
}

void LCD_ScanCard() {
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Scan Your Card>>");
  delay(2000); // Delay for 2 seconds to allow time to present the card 
}

//-------------------helper functions--------------------

void AccessGranted() {
  //Serial.println("Access is granted");
  Serial.println("---------------------------");
  lcd.clear();
  unlockDoor();
  lcd.setCursor(0, 0);
  lcd.print("Welcome!");
  lcd.setCursor(0, 1);
  lcd.print("Door unlocked");
  delay(3000); 
  lockDoor();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Door locked");
  delay(3000); 
  
  lcd.clear();
}

void AccessDenied() {
  //Serial.println("Access is denied");
  Serial.println("---------------------------");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Access Denied!");
  lcd.setCursor(0, 1);
  lcd.print("Unauthorized");
  activateAlarm(1000); 
  delay(5000);
  turnOffAlarm();
  lcd.clear(); 
}

void VisitorDetected() {
  //Serial.println("Visitor is detected!");
  Serial.println("--------------------------");
  lcdVisitor();
  visitor_timer = millis();
}

void lcdVisitor() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello there!");
  lcd.setCursor(0, 1);
  lcd.print("Please wait!");
  tone(buzzer_pin, 500); 
  delay(800);
  noTone(buzzer_pin);
}

void noResponse() {
  lcd.clear();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("No response");
  lcd.setCursor(0, 1);
  lcd.print("Good day!");
  activateAlarm(1000);
  delay(5000);
  turnOffAlarm();
  lcd.clear();
}
void ownerOpened(){
  lcd.clear();
  unlockDoor(); 
  lcd.setCursor(0, 0);
  lcd.print("Welcome In!");
  lcd.setCursor(0, 1);
  lcd.print("owner open");
  delay(3000);
  lockDoor();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("Door locked");
  delay(2000);
  lcd.clear();
}

//-------Setup helper--------------------------------------------
void PIRWarmUp(){
Serial.print("PIR sensor warm up");
  for (int i = 0; i < warm_up_time ; i++)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("SENSOR ACTIVE");
  delay(50);
}
void LCDSetUp(){
  lcd.begin(16, 2);
  lcd.backlight(); 
  lcd.setCursor(0, 0);
  lcd.print("SmartLock System");
  lcd.setCursor(0, 1);
  lcd.print("system warm up");
  delay(2000);
}
