#include <Encoder.h>
#include <PIDController.h>  

PIDController pid;

#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB

int encoder_count = 0; // stores the current encoder count
double tick_to_deg1; 

Encoder myEnc(ENCODER_B, ENCODER_A); 

#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9
double motor_pwm_value;

float kp = 1; //Kp= 0675
float ki = 0.17; //Ki= none
float kd = 0.12; //Kd= -0.015

////////// SETUP //////////
void setup() {
 
  Serial.begin(9600); // print
   // start CD engine
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);
  // Set initial rotation direction
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  // print the desired velocity
  Serial.print("Write the power, in percents you want to send to the motor");

  pid.begin(); // Initialize the PID controller
  pid.limit(-180, 180); // The PID output can be limited to values between -255 to 255
  pid.tune(kp, ki, kd); // Set PID parameters 
  pid.setpoint(0); // the goal angle

}

////////// LOOP //////////
void loop() {

  encoder_count = myEnc.read(); // read the number of rounds until now
  Serial.print("encoder_count = ");
  Serial.println(encoder_count);
  tick_to_deg1 = tick_to_deg(encoder_count); // calculate the degrees based on the number of rounds
  
  // update the real degrees value (back to 0 - 360)
  while (abs(tick_to_deg1) > 360) { 
    if (tick_to_deg1 < 0)
        tick_to_deg1 = tick_to_deg1 + 360;
    else
        tick_to_deg1 = tick_to_deg1 - 360;
  }

  Serial.print("tick_to_deg1 = ");
  Serial.println(tick_to_deg1);  

  //the motor based on current angle 
  motor_pwm_value = double(pid.compute(tick_to_deg1)); // compute the PWM value
    
  // calculate motor direction
  if (motor_pwm_value < 0)
    reverse();
  else 
   forward();
  
  // send PWM value to motor
  analogWrite(enA, abs(255 * motor_pwm_value * 6/100));
  delay(50);
 
}


////////// FUNCTIONS //////////

// clockwise
void forward(){
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
}

// counter-clockwise
void reverse(){
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
}

// convert the tick to degrees
double tick_to_deg(long tick) { 
    return tick * 360.0/440.0; // 440 pulses until full round
}