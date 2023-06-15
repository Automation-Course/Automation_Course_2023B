#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB
#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9
#include <Encoder.h>
#include <PIDController.h>   

float encoder_count; // stores the current encoder count
float tick_to_deg1;
int motor_pwm_value;
int userInput;

PIDController pid;
Encoder myEnc(ENCODER_B, ENCODER_A);

/*******functions******/
void forward(){ // move motor FORWARD
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  }

void reverse(){ //move motor BACKWARDS
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
  }
 
 void get_user_input(){
  userInput = Serial.parseFloat();
  Serial.read();    // get the ENTER char from the serial
  Serial.println(userInput);
}  

float tick_to_deg(long tick){
  return tick*360.0/440.0;
}

/*******setup *******/
void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);
  
  pid.begin(); // Initialize the PID controller
  pid.limit(-255, 255); // The PID output can be limited to values between -255 to 255
  pid.tune(8.7,2,0.62); // Set PID parameters
  
 Serial.print("Write the desired angle: ");
  }

void loop() {
 if (Serial.available()>0){ // Wait for User to Input Data
     get_user_input();
    }
  encoder_count = myEnc.read();
  tick_to_deg1 = tick_to_deg(encoder_count);
  while (abs(tick_to_deg1)>360){
    if (tick_to_deg1<0)
        tick_to_deg1=tick_to_deg1+360;
    else
        tick_to_deg1=tick_to_deg1-360;       
  }
  
  motor_pwm_value = float(pid.compute(tick_to_deg1));  //compute the PWM value for the motor based on current angle

   // calculate motor direction
  if (tick_to_deg1 <userInput ){
    reverse();
  }
  else {
   forward();
  }
  // send PWM value to motor
  analogWrite(enA, abs(motor_pwm_value));
 delay(1);
  }