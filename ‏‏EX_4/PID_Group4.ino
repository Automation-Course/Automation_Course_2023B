#include <PIDController.h>    // https://github.com/DonnyCraft1/PIDArduino
#include <Encoder.h>
PIDController pid;
#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9
#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB

float tick_to_deg1 ;
float encoder_count;
float enc_deg;
int motor_pwm_value;
int goal_degree;
Encoder myEnc(ENCODER_B, ENCODER_A);
float Kp;
float Kd;
float Ki; 

/*******functions******/

float tick_to_deg(long tick){ 
return tick*360.0/440.0;    
}

void forward(){ //turn the motor clockwise
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  }
  

void reverse(){ //turn the motor Counterclockwise
  digitalWrite(MOTOR_CW, LOW);
  digitalWrite(MOTOR_CCW, HIGH);
  }
 
 void get_user_input(){ 
  goal_degree = Serial.parseFloat();  
  Serial.read();   
  while(abs(goal_degree)>360) {
    if(goal_degree>0)
      goal_degree=goal_degree-360;
    else
      goal_degree=goal_degree+360;  
   }
}  
/*******setup *******/
void setup() {
  Kp=7.1;
  Kd=0.9;
  Ki=2.1; 
  Serial.begin(9600);
  pinMode(enA, OUTPUT);
  pinMode(MOTOR_CW, OUTPUT);
  pinMode(MOTOR_CCW, OUTPUT);
  digitalWrite(MOTOR_CW, HIGH);
  digitalWrite(MOTOR_CCW, LOW);
  pid.begin(); // Initialize the PID controller
  pid.limit(-180, 180); 
  pid.tune(Kp, Ki, Kd); // Set PID parameters 
  Serial.print("Please write the angle between 0-360 "); 
  }

void loop() {
  if (Serial.available()>0){ // Wait for User to Input Data
    get_user_input();
  }

  encoder_count = myEnc.read(); //read encoder
  enc_deg = tick_to_deg(encoder_count); //convert to degrees

  while (abs(enc_deg)>360){//keep the angle in the range -360 to 360 deegres
    if (enc_deg<0)
        enc_deg=enc_deg+360;
    else
        enc_deg=enc_deg-360;       
  }

  motor_pwm_value = float(pid.compute(enc_deg));  //compute the PWM value for 					

  if (enc_deg>goal_degree) { //choose the direction to rotate
    forward();
  }
  else { 
     reverse();
  }
  
  analogWrite(enA, abs(motor_pwm_value));
  delay(10);
}






