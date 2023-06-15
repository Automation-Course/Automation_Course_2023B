#include <PIDController.h>
#include <Encoder.h>

// Define:
#define ENCODER_A 2
#define ENCODER_B 3 
#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9

PIDController pid;   
Encoder myEnc(ENCODER_B, ENCODER_A);

float Kp = 35;
float Ki = 2.05;
float Kd = 1800;

float temp;
float goal_deg = 0.0;
float motor_pwm_value;
int encoder_tick_count;  
float encoder_deg = 0.0;
float err_in_deg;
float err_in_tick;
float err_in_percentage;
float error_in_pwm;

// Functions:
float tick_to_deg_fun(long tick)
{
  return (tick * 360.0) / 440.0;
}

float deg_to_tick_fun(float err)
{
  return (err * 440.0) / 360.0;
}

float tick_to_percentage_fun(float err_in_tick)
{
  return (err_in_tick / 440.0) * 100;
}

float percentage_to_pwm_fun(float err_tick)
{
  return (255 * err_tick) / 100.0;
}

void forward()
{
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
}

void reverse()
{
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
}

void get_user_input()
{
  if (Serial.available() > 0)
  {
    goal_deg = Serial.parseFloat()*-2.36;
    Serial.read();      
    pid.setpoint(goal_deg); 
  }
}

void setup()
{
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  pid.begin();         
  pid.limit(-180, 180);  
  pid.tune(Kp, Ki, Kd);   

  Serial.println("Enter goal degree");
}

void loop()
{
  get_user_input();

  encoder_tick_count = myEnc.read(); 
  float prev_encoder_deg = encoder_deg;
  encoder_deg = tick_to_deg_fun(encoder_tick_count);
  float angle_change = encoder_deg - prev_encoder_deg;
  if (angle_change < -180)
  {
    angle_change += 360;
  }
  else if (angle_change > 180)
  {
    angle_change -= 360;
  }


  encoder_deg = prev_encoder_deg + angle_change;

  err_in_deg = goal_deg - encoder_deg;

  Serial.print("deg: ");
  Serial.println(encoder_deg);
  
  err_in_tick = deg_to_tick_fun(err_in_deg);
  err_in_percentage = tick_to_percentage_fun(err_in_tick);
  error_in_pwm = percentage_to_pwm_fun(err_in_percentage);
  motor_pwm_value = float(pid.compute(error_in_pwm));

  if (motor_pwm_value < 0)
    reverse();
  else
    forward();

  analogWrite(enA, abs(motor_pwm_value));
  delay(1);                             
}
