#include <Encoder.h> 
#include <PIDController.h>
#define ENCOD_A 2
#define ENCOD_B 3
#define MOTOR_CCW 11
#define MOTOR_CW 10
#define SPEED 9
PIDController pid;
int motor_pwm_value=0;
int encod_count=0; //save the encod count
float tick_to_deg1=0;
float inputError;

Encoder myEnc(ENCOD_B,ENCOD_A);
/*FUNCTIONS*/
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
void getMotorV () {
   motor_pwm_value=pid.compute(tick_to_deg1);
}


/*SETUP*/
void setup(){
  Serial.begin(9600);
  pinMode(SPEED,OUTPUT);
  pinMode(MOTOR_CW,OUTPUT);
  pinMode(MOTOR_CCW,OUTPUT);
  // Decide direction
  digitalWrite(MOTOR_CW,HIGH);
  digitalWrite(MOTOR_CCW,LOW);
pid.begin();
pid.limit(-180,180); // output can get only these values: -255 to 255
pid.tune(1, 0.1 ,0.1); // PID Parameters
pid.setpoint(0); // goal angle 

}
void loop(){
  encod_count=myEnc.read();
  tick_to_deg1 = tick_to_deg(encod_count);

  if(tick_to_deg1!=0){
    getMotorV();
  }
// Put the PWM value for
    Serial.println(tick_to_deg1);
    if (motor_pwm_value>0){
    reverse (); }
    else{
    forward();
    }
    while (abs(tick_to_deg1)>360){
      if(tick_to_deg1<0)
        tick_to_deg1=tick_to_deg1+360;
      else
        tick_to_deg1=tick_to_deg1-360; 
}

// Output PWM value for the motor
  analogWrite(SPEED, (abs(motor_pwm_value)*255*4)/50);
  delay(1);
}

;