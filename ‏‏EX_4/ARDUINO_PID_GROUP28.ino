#include <Encoder.h>
#include <PIDController.h>

#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB
#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9

int encoder_count = 0; // stores the current encoder count
float tick_to_deg1;
float enc_deg; 
float goal_deg;
int motor_pwm_value; 

Encoder myEnc(ENCODER_B, ENCODER_A);
PIDController pid;

/*****functions****/
float tick_to_deg(long tick) {
  return tick * 360.0 / 440.0;
}

void forward() {
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
}

void reverse() {
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
}

void get_user_input() {
  goal_deg = Serial.parseFloat();
  Serial.read();    // get the ENTER char from the serial
  Serial.println(goal_deg);
}

/*******setup *******/
void setup() {
  Serial.begin(9600);

  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);

  // Set initial rotation direction
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);

  pid.begin(); // Initialize the PID controller
  pid.limit(-255, 255); // The PID output can be limited to values between -255 to 255
  pid.tune(8.9,1.2,0.55); // Set PID parameters
  Serial.println("Write the angle you want");

}

void loop() {
  if (Serial.available() > 0) { // Wait for User to Input Data
    get_user_input();
  }
//convert to real degree 
  encoder_count = myEnc.read();
  tick_to_deg1 = tick_to_deg(encoder_count);
  while (abs(tick_to_deg1)>360){
    if (tick_to_deg1<0)
        tick_to_deg1=tick_to_deg1+360;
    else
        tick_to_deg1=tick_to_deg1-360;       
  }

  enc_deg = tick_to_deg1;
  motor_pwm_value = float(pid.compute(enc_deg)); // Compute the PWM value for the motor based on the current angle

  // calculate motor direction
  if (motor_pwm_value < goal_deg)
    reverse();
  else
    forward();

  // send PWM value to motor
  analogWrite(enA, abs(motor_pwm_value));
Serial.println(tick_to_deg1);
  delay(10);
}