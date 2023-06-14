#include <Encoder.h>
#include <PIDController.h> 
#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB
#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9

int motor_pwm_value;
int encoder_count = 0; // stores the current encoder count
Encoder myEnc(ENCODER_B, ENCODER_A);
PIDController pid;

float kp =60;
float kd =  0.5;
float ki = 0;
float goal_deg; 

/*******functions******/
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
  
void get_user_input(){// gets the goal angle from the user
  goal_deg = (Serial.parseFloat());
  Serial.read();    // get the ENTER char from the serial
  pid.setpoint(goal_deg);
}  
 


/*******setup *******/
void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);


  // Set initial rotation direction
  forward();
  
  pid.begin(); // Initialize the PID controller
  pid.limit(-180, 180); // The PID output can be limited to values between -255 to 255
  pid.tune(kp,ki,kd); // Set PID parameters
  goal_deg = 0;
  pid.setpoint(goal_deg); // the goal angle

 }



void loop() {   
  if(Serial.available()>0){
    get_user_input();
  } 
   
  encoder_count = myEnc.read();

   float enc_deg = tick_to_deg(encoder_count); 

   motor_pwm_value = float(pid.compute(enc_deg));  

  // calculate motor direction
  if (enc_deg <goal_deg )   
    reverse();
    analogWrite(enA, abs(motor_pwm_value));
  if(enc_deg > goal_deg) 
    forward();
    analogWrite(enA, abs(motor_pwm_value));

  Serial.println(enc_deg);
  delay(1);
 
  }
