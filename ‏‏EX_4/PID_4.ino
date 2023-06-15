#include <Encoder.h>
#include <PIDController.h>

#define ENCODER_A 2 //input
#define ENCODER_B 3//output
#define MOTOR_CCW 11 //against clockwise
#define MOTOR_CW 10 //clockwise
#define enA 9

float kP= 15;
float kD =  50;
float kI=3;

//float inputDeg=0;
int motor_pwm_value;
float tick_to_deg1;
int encoder_count=0; //stores the current encoder count
float setpoint = 15;

Encoder encoder(ENCODER_B, ENCODER_A);
PIDController PID;

/*******functions******/
void forward() {
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  }

void reverse() {
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
  }


 float tick_to_deg (long tick) {  //Convert ticks from the encoder to degries
return tick*360.0/440.0;
}


 void getMotorV(){
   motor_pwm_value= PID.compute(tick_to_deg1);
 }
///*
 void get_user_input(){
  setpoint = Serial.parseFloat();
  Serial.read();    // get the ENTER char from the serial
}  
//*/


/*******setup *******/
void setup() {
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);

  // Set initial rotation direction. assuming the motor init to spin clockwise
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);

  PID.begin();
  PID.limit(-180,180); // PID output can be limited between -255 to 255 
  PID.tune(kP,kI,kD); //SET PID PARAMETERS
   //setpoint=get_user_input();
  // inputDeg += tick_to_deg(encoder_count);
    //setpoint = get_user_input(); // Update the setpoint value from the user
//get_user_input();
  }

void loop() {
   PID.setpoint(setpoint); //the wanted angle
   encoder_count = encoder.read();
   tick_to_deg1 = tick_to_deg(encoder_count); // degrees from the encoder
   motor_pwm_value= PID.compute(tick_to_deg1); // Calc the pwm value for the motor using the degress from the encoder read

 if (tick_to_deg1 < setpoint){ // Wait for User to Input Data
     reverse();
    }
else {
forward();
}

analogWrite(enA, abs(motor_pwm_value));
delay(1);
Serial.println(tick_to_deg1);//מדפיס לנו את הערך שהמחוגה נמצאת

}



