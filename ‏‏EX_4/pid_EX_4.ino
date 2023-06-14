#include <Encoder.h>
#include <PIDController.h>

//pins
#define MOTOR_CCW 10
#define MOTOR_CW 11 
#define enA 9 
int encoderPin2 = 2; 
int encoderPin3 = 3; 

// PID constants
float kp = 1; // Proportional gain constant for PID control
float ki = 0.17; // Integral gain constant for PID control
float kd = 0.12; // Derivative gain constant for PID control
float targetAngle = 0.0; // Target angle for the pendulum
float setpoint; // Current setpoint for the PID controller
double angle = 0.0; // Current angle of the pendulum


// Global variables
Encoder encoder(encoderPin2, encoderPin3); // Encoder object for reading encoder values
PIDController pidController; // PIDController object for PID control

// Convert encoder ticks to degrees
float tick_to_deg(long tick) {
    return tick * 360.0 / 440.0;
}

// Move the motor forward
void moveForward() {
  digitalWrite(MOTOR_CCW, HIGH);
  digitalWrite(MOTOR_CW, LOW);
}

// Move the motor in reverse
void moveReverse() {
  digitalWrite(MOTOR_CCW, LOW);
  digitalWrite(MOTOR_CW, HIGH);
}

// Get user input from serial
void getUserInput() {
  if (Serial.available() > 0) {
    float userInput = Serial.parseFloat();
    Serial.read();    // Get the ENTER character from the serial buffer
    setpoint = userInput; // Assign the user input to the setpoint variable
    pidController.setpoint(setpoint);
  }
}

// Setup function
void setup() {
  // Initialize motor pins as output
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pidController.begin(); // Initialize the PID controller
  pidController.limit(-180, 180); // Set the output limits of the PID controller
  pidController.tune(kp, ki, kd); // Set PID parameters
  pidController.setpoint(targetAngle); // Set the target angle for the PID controller
}

// Loop function
void loop() {

  // Read encoder and calculate current angle of the pendulum
  long encoderCount = encoder.read();
  angle = tick_to_deg(encoderCount);
  getUserInput();
  // Calculate control signal its the difference of angle between the current angle and the goal angle
  double control = pidController.compute(angle);


  Serial.print("angle:");
  Serial.println(angle);
  // Serial.print("targetAngle:");
  // Serial.println(targetAngle);


  if (control > 0.0) {
    moveForward();
  } else {
    moveReverse();
  }
  // Send PWM power to motor , we started by doing 255/100 but after afew try we understood that 255*4/100 give better results
  analogWrite(enA, abs(control * 10.2));
}