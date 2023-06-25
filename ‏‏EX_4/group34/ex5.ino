#include <Encoder.h>
#include <PIDController.h>

#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB
#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9

int encoder_count = 0; // stores the current encoder count
float tick_to_deg1 ;
Encoder myEnc(ENCODER_B, ENCODER_A);
float motor_pwm_value;
PIDController pid;

double Kp= 15 ;
double Ki= 0.9 ;
double Kd= 350 ;
float deg_desirable;

/**functions***/
float tick_to_deg(long tick){
    return tick*360.0/440.0;
  }

void forward(){
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  }

void reverse(){
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
  }
 
 void get_user_input(){
  deg_desirable = Serial.parseFloat();
  Serial.read();    // get the ENTER char from the serial
  pid.setpoint(deg_desirable); // the goal angle
  }
  

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);
  // Set initial rotation direction
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  
  pid.begin(); // Initialize the PID controller
  pid.limit(-255,255); // The PID output can be limited to values between -255 to 255
  pid.tune(Kp, Ki, Kd); // Set PID parameters
  pid.setpoint(deg_desirable); // the goal angle

  Serial.print("Write the angle between -15 to 15 degrees, you want the system to stabilize at");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()>0){ // Wait for User to Input Data
     get_user_input();
    }
    
  encoder_count = myEnc.read();
  Serial.print("encoder_count = ");
  Serial.println(encoder_count);
  tick_to_deg1 = tick_to_deg(encoder_count);
    while (abs(tick_to_deg1)>360){
    if (tick_to_deg1<0)
       tick_to_deg1=tick_to_deg1+360;
    else
       tick_to_deg1=tick_to_deg1-360;       
  }
  Serial.print("tick_to_deg1 = ");
  Serial.println(tick_to_deg1);
  motor_pwm_value = float(pid.compute(tick_to_deg1));  //compute the PWM value for the motor based on current angle
   // calculate motor direction
  if (tick_to_deg1 < deg_desirable ){
    reverse();
  }
  else{
    forward();
  } 
  analogWrite(enA, abs(motor_pwm_value));
  // send PWM value to motor
  

}