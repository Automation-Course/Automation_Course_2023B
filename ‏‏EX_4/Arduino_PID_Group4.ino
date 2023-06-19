#include <Encoder.h>
#include <PIDController.h>

#define ENCODER_A 2 // Input
#define ENCODER_B 3 // Output
#define MOTOR_CCW 11 // Against clockwise
#define MOTOR_CW 10 // Clockwise
#define enA 9

float kP = 30;
float kD = 50;
float kI = 2;



int motor_pwm_value;
float tick_to_deg1;
int encoder_count = 0; // Stores the current encoder count
float setpoint = 0;

Encoder encoder(ENCODER_B, ENCODER_A);
PIDController PID;

void rotateClockwise() {
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
}

void rotateCounterClockwise() {
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
}

float convertTicksToDegrees(long tick) { // Convert ticks from the encoder to degrees
  return tick * 360.0 / 440.0;
}

void getUserInput() {
  float input = Serial.parseFloat();
  Serial.read(); // Get the ENTER char from the serial

  if (abs(input) > 15 || abs(input) <-15 ) {
    Serial.println("Invalid setpoint value. Resetting to zero.");
    setpoint = 0;
  } else {
    setpoint = input;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);

  // Set initial rotation direction. Assuming the motor is initialized to spin clockwise
  rotateClockwise();

  PID.begin();
  PID.limit(-180, 180); // PID output can be limited between -255 to 255
  PID.tune(kP, kI, kD); // Set PID parameters
}

void loop() {
  if (Serial.available() > 0) {
    getUserInput();
  }

  PID.setpoint(setpoint); // The desired angle
  encoder_count = encoder.read();
  tick_to_deg1 = convertTicksToDegrees(encoder_count); // Degrees from the encoder
 while (abs(tick_to_deg1)>360){
    if (tick_to_deg1<0)
        tick_to_deg1=tick_to_deg1+360;
    else
        tick_to_deg1=tick_to_deg1-360;       
  }

  motor_pwm_value = PID.compute(tick_to_deg1); // Calculate the PWM value for the motor using the degrees from the encoder read

  if (tick_to_deg1 < setpoint) {
    rotateClockwise();
  } else {
    rotateCounterClockwise();
  }

  analogWrite(enA, abs(motor_pwm_value));
  delay(1);
  Serial.println(tick_to_deg1); // Print the angle value from the encoder
}
