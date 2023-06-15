#include <Encoder.h>
#include <PIDController.h>    
#define ENCODER_A 2 
#define ENCODER_B 3
#define enA 9
#define MOTOR_CW 10
#define MOTOR_CCW 11

Encoder myEnc(ENCODER_B, ENCODER_A);
PIDController pid;

int motor_pwm_value; 
int encoder_count = 0;
float tick_to_deg1;
float temp_degree;
float Kp = 100;
float Ki = 0;
float Kd = 1;
float goal_deg;

// --------------------- SETUP --------------------------------------------
void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);

  // Set initial rotation direction
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  
  pid.begin(); // Initialize the PID controller
  pid.limit(-180, 180); // The PID output can be limited to values between -255 to 255
  pid.tune(Kp, Ki, Kd);
  Serial.println("");
  Serial.println("Please choose a degree between -15 to 15");
 }

// --------------------- LOOP --------------------------------------------
void loop() {

  if (Serial.available() > 0) {
    get_user_input(); 
  }

  encoder_count = myEnc.read();
  tick_to_deg1 = tick_to_deg(encoder_count);
  no_more_than_360();

  motor_pwm_value = float(pid.compute(tick_to_deg1));  

   // calculate motor direction
  motorDirection();
  
  // send PWM value to motor
  analogWrite(enA, abs(motor_pwm_value));
  delay(1);
}


// --------------------- FUNCTIONS --------------------------------------------
float tick_to_deg(long tick){
    return tick*360.0/440.0;
}

void forward(){
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
}

void reverse(){
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
}
 
void get_user_input(){
  temp_degree = Serial.parseFloat();
  Serial.read();

  if (temp_degree < -15 || temp_degree > 15) {
    Serial.println("Please choose a degree between -15 to 15");
  }
  else {
    goal_deg = temp_degree;
    pid.setpoint(goal_deg);
    Serial.print("----------------------- Goal_deg is: ");
    Serial.println(goal_deg);
  }
}

void no_more_than_360() {
  while (abs(tick_to_deg1) > 360) {
    if(tick_to_deg1 < 0) {
      tick_to_deg1 = tick_to_deg1 + 360;
    }
    else {
      tick_to_deg1 = tick_to_deg1 - 360;
    }
  }
}

void motorDirection() {
  if (tick_to_deg1 > goal_deg) {
    reverse();
  }
  else {
    forward();
  }
}
