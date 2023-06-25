#include <Encoder.h>
#include <PIDController.h>

PIDController pid;

#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB
#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9
double motor_pwm_value;
float enc_degree=0;
int tempInput;
int degreeInput;
int encoder_count = 0; // stores the current encoder count

Encoder myEnc(ENCODER_B, ENCODER_A);


float kp = 15; //KP=
float ki = 2.2; //KI=
float kd = 1; //KD=

 
void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);

  // Set initial rotation direction
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  
  
  pid.begin(); // Initialize the PID controller
  pid.limit(-180, 180); // The PID output can be limited to values between -255 to 255
  pid.tune(kp, ki, kd); // Set PID parameters
  pid.setpoint(degreeInput); // the goal angle
  Serial.print("Enter the Angle");
}
  
   void forward(){
    digitalWrite(MOTOR_CW, HIGH);
    digitalWrite(MOTOR_CCW, LOW);
  }

  void reverse(){
    digitalWrite(MOTOR_CW, LOW);
    digitalWrite(MOTOR_CCW, HIGH);
  }
 
  float tick_to_deg(long tick){
    return tick*360.0/440.0;
  }
  void get_user_input(){
  tempInput = Serial.parseFloat();
  Serial.read();    // get the ENTER char from the serial
  if (tempInput<-15 || tempInput>15) {
      Serial.print("Enter an Angle between -15 to 15 degrees");
  }
  else 
    degreeInput = tempInput;
  
  }

void loop() {
    Serial.println(enc_degree);
  if (Serial.available()>0){ // Wait for User to Input Data
     get_user_input();
  }
  encoder_count = myEnc.read();
  enc_degree = tick_to_deg(encoder_count);
  while (abs(enc_degree)>360){
      if (enc_degree<0)
        enc_degree=enc_degree+360;
      else
        enc_degree=enc_degree-360;       
  }
  motor_pwm_value = float(pid.compute(enc_degree)); // calculate motor direction
  if (enc_degree < degreeInput)
    reverse();
  else 
   forward();
  analogWrite(enA, abs(motor_pwm_value));
  delay(1); 
}