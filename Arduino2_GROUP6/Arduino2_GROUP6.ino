#define MOTOR_CCW 11
#define MOTOR_CW 10
#define enA 9
#include <PIDController.h>    // https://github.com/DonnyCraft1/PIDArduino
#include <Encoder.h>
#define ENCODER_A 2 
#define ENCODER_B 3 // Encoder output to Arduino Interrupt pin ncoderPinB

PIDController pid;

float tick_to_deg1 ;
float encoder_count;
float enc_deg;
int motor_pwm_value;
int Power_In_Percents;
int userInput;
Encoder myEnc(ENCODER_B, ENCODER_A);


/*******functions******/

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
  userInput = Serial.parseFloat();  // the goal angle
  Serial.read();    // get the ENTER char from the serial
  
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
pid.limit(-180, 180); // The PID output can be limited to values between -255 to 255
pid.tune(7, 2, 1); // Set PID parameters

Serial.print("Write the angle you want");

  
  }
void loop() {
 

 if (Serial.available()>0){ // Wait for User to Input Data
     get_user_input();
    }

  encoder_count = myEnc.read();
  enc_deg = tick_to_deg(encoder_count);

    while (abs(enc_deg)>360){//keep the angle in the range -360 to 360 deegres
    if (enc_deg<0)
        enc_deg=enc_deg+360;
    else
        enc_deg=enc_deg-360;       
  }

  motor_pwm_value = float(pid.compute(enc_deg));  //compute the PWM value for 					//the motor based on current angle


  if (enc_deg>userInput) {
    forward();
  }
  else { 
     reverse();
  }
  // send PWM value to motor
  analogWrite(enA, abs(motor_pwm_value));

 
 delay(1);
  }






