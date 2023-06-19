•	#include <Encoder.h>
•	#include <PIDController.h >
•	
•	// Motor and pin definitions
•	#define MOTOR_CCW 11
•	#define MOTOR_CW 10
•	#define enA 9
•	#define ENCODER_A 2
•	#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB
•	
•	int pwm_value;
•	int power_Percents; // Power of DC motor
•	PIDController pid;
•	int encoder_count = 0; // Stores the current encoder count
•	float tick_to_deg1;
•	double Kd = 4.1; // Derivative gain for PID controller
•	double Ki = 1.7; // Integral gain for PID controller
•	double Kp = 10; // Proportional gain for PID controller
•	float final_deg = 0; // Desired final angle for the pendulum
•	Encoder myEnc(ENCODER_B, ENCODER_A); // Encoder object for reading the pendulum angle
•	
•	void setup() {
•	  Serial.begin(9600);
•	  pinMode(enA, OUTPUT);
•	  pinMode(MOTOR_CW, OUTPUT);
•	  pinMode(MOTOR_CCW, OUTPUT);
•	
•	  // Set initial rotation direction
•	  digitalWrite(MOTOR_CW, HIGH);
•	  digitalWrite(MOTOR_CCW, LOW);
•	
•	  pid.begin(); // Initialize the PID controller
•	  pid.limit(-180, 180); // The PID output can be limited to values between -180 to 180
•	  pid.tune(Kp, Ki, Kd); // Set PID parameters
•	  pid.setpoint(final_deg); // Set the desired final angle for the pendulum
•	  Serial.println("Enter the final degree you want the pendulum to be:");
•	}
•	
•	void loop() {
•	  if (Serial.available() > 0) {
•	    get_user_input();
•	  }
•	
•	  encoder_count = myEnc.read();
•	  tick_to_deg1 = tick_to_deg(encoder_count); // Convert the encoder count to degrees
•	
•	  // Ensure the degree value is between 0-360
•	  while (abs(tick_to_deg1) > 360) {
•	    if (tick_to_deg1 < 0)
•	      tick_to_deg1 = tick_to_deg1 + 360;
•	    else
•	      tick_to_deg1 = tick_to_deg1 - 360;
•	  }
•	
•	  // Print the current degree and the final degree
•	  Serial.print("tick_to_deg1 = ");
•	  Serial.println(tick_to_deg1);
•	  //Serial.print("final degree = ");
•	  //Serial.println(final_deg);
•	
•	  delay(10);
•	  pwm_value = float(pid.compute(tick_to_deg1));
•	
•	  // Change the motor direction according to the error
•	  if (pwm_value < 0)
•	    reverse();
•	  else
•	    forward();
•	
•	  // Send PWM value to the motor
•	  analogWrite(enA, abs(pwm_value));
•	  delay(1);
•	}
•	
•	// Functions
•	
•	// Convert encoder tick to degrees
•	float tick_to_deg(long tick) {
•	  return tick * 360.0 / 440.0;
•	}
•	
•	// Set the motor to rotate forward
•	void forward() {
•	  digitalWrite(MOTOR_CW, HIGH);
•	  digitalWrite(MOTOR_CCW, LOW);
•	}
•	
•	// Set the motor to rotate in reverse
•	void reverse() {
•	  digitalWrite(MOTOR_CW, LOW);
•	  digitalWrite(MOTOR_CCW, HIGH);
•	}
•	
•	// Get the desired final angle input from the user
•	void get_user_input() {
•	  final_deg = Serial.parseFloat();
•	  Serial.read();
•	}
