#include <Encoder.h>
#include <PIDController.h>    // https://github.com/DonnyCraft1/PIDArduino


// Define the encoder pins
#define ENCODER_A 2 
#define ENCODER_B 3 


// Define the pins for motor control
#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9

// Define the PID controller encoder
PIDController pid;
Encoder myEnc(ENCODER_B, ENCODER_A);

// Variables
float kp ;
float kd;
float ki;
float goal_deg=0.0; //angle for the pendulum
float encoder_count =0;


// /*******Setup *******/
void setup() {
  Serial.begin(9600);

  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);
  pinMode(enA, OUTPUT);

  // Ask user for degree input
  goal_deg = get_input_from_user();

  // Ask user for PID input
  kp = get_kp();
  ki = get_ki();
  kd = get_kd();
  
  // initial rotation direction
  forward();


  // Initialize PID controller
  pid.begin(); // Initialize the PID controller
  pid.setpoint(goal_deg); // Set the goal angle
  pid.limit(-90, 90); // The PID output can be limited to values between -255 to 255
  pid.tune(kp, ki, kd); // Set PID parameters
}


void loop() {

  // Read the current position of the encoder
  encoder_count = tick_to_deg(myEnc.read());

  float motor_pwm_value = float(pid.compute(encoder_count));

  Serial.print(goal_deg);
  Serial.print(","); 
  Serial.println(encoder_count);


  // the motor speed limit
  motor_pwm_value = constrain(motor_pwm_value, -250, 250);


  // Set the motor direction and speed using the H-bridge driver
  if (motor_pwm_value < 0){
    reverse();
    analogWrite(enA, -motor_pwm_value);// Send PWM value to motor
  }
  else {
    forward();
    analogWrite(enA, motor_pwm_value);// Send PWM value to motor
}

  delay(1);
}

// Functions to control motor direction
void forward() {
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
}

void reverse() {
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
}

// Function to check if input is available from the user
bool check_input() {
  return Serial.available() > 0;
}

// Functions to get input from the user 
float get_input_from_user(){
  Serial.println("");  
  Serial.println("Insert the degree for the pendulum (-15 to 15):");  
  bool validation = false;

  while (!validation){
    while (!check_input()){}
    goal_deg = Serial.parseFloat();
    Serial.readStringUntil('\n');
    Serial.println("The chosen degree:");
    Serial.println(goal_deg);
    if (goal_deg >= -15 && goal_deg <= 15) {
      validation = true;
    } 
    else {
      validation = false;
      Serial.println("Input not valid. try again!");  
    }
  }
  return goal_deg;
}

float get_kp(){
  Serial.println("Insert kp:");  
  while (!check_input()){}
  String input = Serial.readStringUntil('\n'); 
  kp = input.toFloat();
  Serial.read();
  Serial.println("Your chosen kp:");
  Serial.println(kp);
  return kp;
}

float get_ki(){
  Serial.println("Insert ki:");  
    while (!check_input()){}
    String input = Serial.readStringUntil('\n');
    ki = input.toFloat();
    Serial.read();
    Serial.println("Your chosen ki:");
    Serial.println(ki);
  return ki;
}

float get_kd(){
  Serial.println("Insert kd:");  
    while (!check_input()){}
    String input = Serial.readStringUntil('\n');
    kd = input.toFloat();
    Serial.read();
    Serial.println("Your chosen kd:");
    Serial.println(kd);
  return kd;
}

// Function change from tick motor count (440) to degree 
float tick_to_deg(long tick){
    return tick*360.0/440.0;
  }

