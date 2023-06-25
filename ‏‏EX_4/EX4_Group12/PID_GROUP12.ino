#include <PIDController.h>
#include <Encoder.h>

PIDController pid;
Encoder myEnc(2, 3);  // Create an instance of the Encoder library and initialize with pins 2 and 3


int MOTOR_CCW = 11;
int MOTOR_CW = 10;
int enA = 9;
int goal_degree;
float tick_to_deg1;
float encoder_count;
float motor_pwm_value;
float Kp = 14;
float Ki = 0.9;
float Kd = 2;

void forward() {
  digitalWrite(MOTOR_CW, HIGH);  // Set the CW pin to HIGH for forward motion
  digitalWrite(MOTOR_CCW, LOW);   // Set the CCW pin to LOW for forward motion
}


void reverse() {
  digitalWrite(MOTOR_CW, LOW);  // Set the CW pin to LOW for reverse motion
  digitalWrite(MOTOR_CCW, HIGH);  // Set the CCW pin to HIGH for reverse motion
}

void LessThan_360(int goal){   // Keep reducing the goal angle if it is larger than 360 degrees
  while (abs(goal) > 360) {
      if (goal > 0)
        goal = goal - 360;
      else
        goal = goal + 360;
    }
}

float tick_to_deg(long tick) {
  return tick * 360.0 / 440.0;
}

void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  pid.begin();
  pid.limit(-180, 180);  // Set the output limit of the PID controller to -180 to 180 degrees
  pid.tune(Kp, Ki, Kd);
  Serial.print("write the angle between (-15, +15) : ");
}  


void loop() {

  if (Serial.available() > 0) {   // Check if there is data available in the serial buffer
    goal_degree = Serial.parseFloat();
    LessThan_360(goal_degree);
    Serial.read();  // Clear the serial buffer

    if (goal_degree>-15 && goal_degree<15){  // Check if the desired angle is within the valid range
      pid.setpoint(goal_degree);
      Serial.print("Goal Degree: ");
      Serial.println(goal_degree);
    } else
       Serial.println("Try again with angle between (-15, +15) :");
       Serial.println();


  }

  encoder_count = myEnc.read();   // Read the current encoder tick count
  tick_to_deg1 = tick_to_deg(encoder_count);
  LessThan_360(tick_to_deg1);

  motor_pwm_value = pid.compute(tick_to_deg1);
  
  if (tick_to_deg1 > goal_degree)   // Check if the current angle is greater than the desired angle
    reverse();  // Move the motor in the reverse direction
  else
    forward();  // Move the motor in the forward direction

  analogWrite(enA, abs(motor_pwm_value));  // Set the motor speed using the computed PWM value

  delay(10);
  Serial.print("tick_to_deg1: ");
  Serial.println(tick_to_deg1);

}