#include <PIDController.h>
#include <Encoder.h>

#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB
#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9

PIDController pid;
Encoder myEnc(ENCODER_B, ENCODER_A);
int encoder_count = 0; // stores the current encoder count
float tick_to_deg1 ;
float kp = 26.7;
float ki = 0;
float kd = 0;
float goal_deg = 0;
float gap;
float y = 0;
int motor_pwm_value;
int Power_In_Percents = 1;

//  Convert encoder number of ticks count to degrees for the dc motor
float tick_to_deg(long tick){ 
    return tick*360.0/440.0;
  }

// Manage the encoder operation - read and restart of values
void operate_encoder_reader(){
  encoder_count = myEnc.read();
  // Serial.print("encoder_count = ");
  // Serial.println(encoder_count);
  tick_to_deg1 = tick_to_deg(encoder_count); // Read the current encoder value
  // Restart the encoder counts when full circle has been made
  while (abs(tick_to_deg1)>360){
    if (tick_to_deg1<0)
        tick_to_deg1=tick_to_deg1+360;
    else
        tick_to_deg1=tick_to_deg1-360;       
  }
  // Serial.print("tick_to_deg1 = ");
  // Serial.println(tick_to_deg1);
  delay(100);
}

// Control the H bridge to set the direction of the dc motor
void forward(){
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  }

void reverse(){
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
  }
 
// Gets from the user the input of the desire degree of the system and set the pid parameters - goal, ki, kd and kp
void get_user_input(){
  goal_deg = Serial.parseFloat();
  Serial.read();    // get the ENTER char from the serial

  pid.tune(kp, ki, kd); // Set PID parameters
  pid.setpoint(goal_deg); // Set the goal angle
}  

// Operate the dc motor - set value and the direction
void operate_dc_motor(){
   // calculate motor direction
  if (motor_pwm_value <0 )
    reverse();
  else 
   forward();
  // send PWM value to motor
  analogWrite(enA, abs(motor_pwm_value));
}

// Setup function
void setup () {
  Serial.begin(9600);
  pid.begin(); // Initialize the PID controller
  pid.limit(-255, 255); // The PID output can be limited to values between -255 to 255
  // Set the pin mode and number
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);
  // Set initial rotation direction to deafult
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
}

// Main loop
void loop () {
  // Check for user input available
  if (Serial.available()>0){
    get_user_input();
  }
  operate_encoder_reader(); // Run the encoder
  gap = abs(tick_to_deg1-goal_deg); 
  if(gap > 15)  // The system requierments for the gap needed from the desire angle
    motor_pwm_value = pid.compute(tick_to_deg1/100);  // Set the current adjustment angle needed
    operate_dc_motor(); // Run the dc motor
    y = 1+(abs(tick_to_deg1/goal_deg)/100); // Calculate the error precentage
    // Print the output value
    Serial.print("The y(t) Output: ");
    Serial.println(y);
    Serial.println(y);  // Print the value of y for the Serial Plotter

}
