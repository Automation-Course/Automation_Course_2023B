#include <PIDController.h>    
#include <Encoder.h>

#define ENCODER_A 2 
#define ENCODER_B 3 
#define enA 9
#define MOTOR_CW 10
#define MOTOR_CCW 11

PIDController pid;

float encoder_count=0;
float enc_degree=0;
int tempInput;
int degreeInput;
int motor_pwm_value;
int Power_In_Percents;

Encoder myEnc(ENCODER_B, ENCODER_A);

float Kp=10;
float Ki=2;
float Kd=2;


void forward(){ //help the move function to move forward
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  }
  

void reverse(){ //help the move function to move reverse 
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
}

float tick_to_deg(long tick){ //440 פולסים לסיבוב מלא
return tick*360.0/440.0;    
}
 
 void GetInput(){ 
  tempInput = Serial.parseFloat();
  Serial.read(); 
  if (tempInput<-15 || tempInput>15){ //check the degree 
    Serial.print("Please write angle between -15 degrees to 15 degrees");
  }
  else{
    degreeInput = tempInput; 
  }
}  
void normalto360(){//keep the angle in the range -360 to 360 deegres
  if (abs(enc_degree)>360){
      if (enc_degree<0)
          enc_degree=enc_degree+360;
      else
          enc_degree=enc_degree-360;       
  }
}

void checkmove(){ //check the needed direction 
  if (enc_degree>degreeInput)  
      forward();
  else 
      reverse();
}

void setup() {
  //define pins
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);

  // Set initial rotation direction
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);

pid.begin(); // Initialize the PID controller
pid.limit(-180, 180); // The PID output can be limited to values between -255 to 255
pid.tune(Kp, Ki, Kd); // Set PID parameters - Kp,Ki,Kd
pid.setpoint(0);
Serial.print("Write the angle you want to send to the motor");
  }
void loop() {
    Serial.println(enc_degree);
 if (Serial.available()>0){ 
     GetInput();
    }
  encoder_count = myEnc.read();
  enc_degree = tick_to_deg(encoder_count);
  normalto360();
  motor_pwm_value = float(pid.compute(enc_degree));  
  checkmove();
  analogWrite(enA, abs(motor_pwm_value));
  delay(1);
  }


