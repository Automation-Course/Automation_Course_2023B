#include <Encoder.h> 
#include <PIDController.h>

PIDController pid; 
#define MOTOR_CCW 11 
#define MOTOR_CW 10 
#define enA 9
#define ENCODER_A 2 
#define ENCODER_B 3

double motor_pwm_value; 
int encoder_count = 0;
double tick_to_deg1; 
Encoder myEnc(ENCODER_B, ENCODER_A);

int angle;
float kp = 1.9; 
float ki = 0.13; 
float kd = 0.95;

void setup() 
{ 
  angle = 0;
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
  Serial.print("Please enter an angle between -180 and 180");
  }

void reverse()
{
   digitalWrite(MOTOR_CW, LOW);
    digitalWrite(MOTOR_CCW, HIGH); 
}

void forward()
{
  digitalWrite(MOTOR_CW, HIGH); 
  digitalWrite(MOTOR_CCW, LOW); 
}

double tick_to_deg(long tick)
{ 
    return tick*360.0/440.0; 
}

void get_user_input()
{
  angle = Serial.parseFloat();
  if (angle < -180 || angle > 180) {
    Serial.println("Error: Angle out of range!"); // Display the error message
    get_user_input();
  }
  Serial.read();   
  Serial.print(angle);
}  

void loop() 
{ 
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
    if (Serial.available() > 0){ // Wait for User to Input Data
        get_user_input();
    }
     pid.setpoint(angle);
    motor_pwm_value = pid.compute(tick_to_deg1); 
    if (motor_pwm_value < 0) 
    reverse(); 
    else 
    forward(); // send PWM value to motor

    analogWrite(enA, abs(255*motor_pwm_value*4/100)); 
    delay(50); 
    Serial.print("tick_to_deg1 = "); 
    Serial.println(tick_to_deg1);
}