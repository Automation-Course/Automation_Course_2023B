#include <Encoder.h>
#include <PIDController.h>

#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9
#define ENCODER_A 2
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB

int motor_pwm_value;
int Power_In_Percents; //power of dc motor
PIDController pid;
int encoder_count = 0; // stores the current encoder count

double Kp= 9.1 ;
double Ki= 1.3 ;
float tick_to_deg1;
double Kd= 0.65 ;
float goal_deg=0;
Encoder myEnc(ENCODER_B, ENCODER_A);


//double Ki= 0.1345 ;


//double Kp=14  ;
//double Ki= 0.255 ;
//float tick_to_deg1;
//double Kd=0.515 ;
//float goal_deg=0;
//Encoder myEnc(ENCODER_B, ENCODER_A);




void reverse(); // Function declaration

//setup
void setup (){
  Serial.begin (9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);
  // Set initial rotation direction
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  pid.begin(); // Initialize the PID controller
  pid.limit(-255, 255); //
  //The PID output can be limited to values between -255 to 255
  pid.tune(Kp, Ki, Kd); // Set PID parameters
  pid.setpoint(goal_deg); // the goal angle
  Serial.print("Write the goal degree you want the pendulum to be:");
}

void loop (){
  if (Serial.available()>0){
    get_user_input();
  }

  encoder_count = myEnc.read();
  tick_to_deg1 = tick_to_deg(encoder_count); //change the encoder to degree
  while (abs(tick_to_deg1)>360) { // change back to range 0-360
    if (tick_to_deg1<0){
      tick_to_deg1=tick_to_deg1+360;
    }
    else{
      tick_to_deg1=tick_to_deg1-360;
    }
  }

  // prints the current deg and the goal deg
  Serial.print("tick_to_deg1 = ");
  Serial.println(tick_to_deg1);
  Serial.print("goal degree = ");
  Serial.println(goal_deg);
  delay(10);
  motor_pwm_value = float(pid.compute(tick_to_deg1)) ;

  // changes the direction due to the error

  if (motor_pwm_value <0 ){
    reverse();
  }
  else{
    forward();
  }

  // send PWM value to motor
  analogWrite(enA, abs(motor_pwm_value));
  delay(1);
}

// New function to handle user input
void get_user_input() {
  goal_deg = Serial.parseFloat();
      Serial.read();
  if (abs(goal_deg) > 15) {
    Serial.print("put another number les than 15 degree");
  }
  else{
    pid.setpoint(goal_deg);
  }
}


//functions
float tick_to_deg(long tick){
 return tick*360.0/440.0;
}

//functions
void forward(){
 digitalWrite(MOTOR_CW, HIGH);
 digitalWrite(MOTOR_CCW, LOW);
}

void reverse(){
 digitalWrite(MOTOR_CW, LOW);
 digitalWrite(MOTOR_CCW, HIGH);
}