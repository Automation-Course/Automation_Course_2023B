//library
#include <PIDController.h>
#include <Encoder.h>

//input output in arduino
#define enA 9
#define ENCODER_A 2
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB
#define MOTOR_CCW 11// Motor defining
#define MOTOR_CW 10


//variebles
float MotorOutput = 0;
float InputForPid= 0;
float tickToDeg = 0;
float motorValue = 0;
float WantedAngle = 0;
float currentDeg = 0;
float EncoderCount = 0;


//constants
float Kp = 3;
float Ki = 0.15;
float Kd = 9;

PIDController pid; //initial pid controler
Encoder myEnc(ENCODER_A, ENCODER_B);



//setup
void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);
  pid.begin(); // initialize the PID
  pid.limit(-180, 180); // Limit the PID output between 0 and 255, this is
  pid.tune(Kp, Ki, Kd); // Tune the PID, arguments: kP, kI, kD
  pid.setpoint(WantedAngle); // The angle the PID tries to reach
  Serial.print("Enter the degree between -15 to +15 degrees:");
}

void loop() {
  if (Serial.available()>0){ // User needs to Input angle
    WantedAngle = Serial.parseFloat();

    if(WantedAngle>15){//max input angle is +-15
    WantedAngle = 15;
    }

    if (WantedAngle<-15){
    WantedAngle = -15;
    }


    Serial.read(); // read the input from serial
    pid.setpoint(WantedAngle);
  } 

  currentDeg = get_degree();
  Serial.println(currentDeg);
  motorValue = pid.compute(currentDeg); //compute the PWM value for the motor based on current angle 
  MotorOutput = abs(255*motorValue*4/100);

  if (motorValue > 0.0) {
    forward();
  } else {
    reverse();
  }
  analogWrite(enA, MotorOutput); // send value to motor



//functions
float get_degree()
{
  EncoderCount = myEnc.read();
  tickToDeg = tick_to_deg(EncoderCount);
  return tickToDeg;
}
float tick_to_deg(long tick){
return tick*360.0/440.0;
}
void forward(){
digitalWrite(MOTOR_CW, HIGH);
digitalWrite(MOTOR_CCW, LOW);
}
void reverse(){
digitalWrite(MOTOR_CW, LOW);
digitalWrite(MOTOR_CCW,HIGH);
}

}