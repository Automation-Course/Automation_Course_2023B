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
float deg= 0; //Stores the degree the motor will end up in

// Calculated values
float kp = 28;
float ki = 2;
float kd =  7;

/**functions***/
float tick_to_deg(long tick){
    return tick*360.0/440.0;
  }

// Move the motor forward
void forward(){
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  }

// Move the motor backword
void reverse(){
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
  }
 


/**setup ****/
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
  pid.setpoint(deg); // the degree the angle will end up in

 }


// Get the input for the degree
 void input_deg()
{
  float input = Serial.parseFloat();
  if (input < -15 || input > 15) {
    Serial.println("engle between -15 and 15"); // Display the error message
  }
  else
  {
    deg = input; 
  }   
}  



void loop() {    
   
  encoder_count = myEnc.read();

  float enc_deg = tick_to_deg(encoder_count); 
  
  while (abs(enc_deg)>360){
    if (enc_deg<0)
        enc_deg=enc_deg+360;
    else
        enc_deg=enc_deg-360;       
  }

  motor_pwm_value = float(pid.compute(enc_deg));  

  // Get the input
  if (Serial.available() > 0){ // Wait for User to Input Data
        input_deg();
        //Serial.println(deg);
        Serial.read();
        pid.setpoint(deg);
    }

  
  // Calculate motor direction
  if (enc_deg < deg)   
    reverse();
    analogWrite(enA, abs(motor_pwm_value));
if(enc_deg > deg) 
    forward();
    analogWrite(enA, abs(motor_pwm_value));

  Serial.println(enc_deg);
 
  }