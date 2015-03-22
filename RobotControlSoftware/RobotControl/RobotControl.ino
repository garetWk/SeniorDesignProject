

/*
 * ---------------------------------------------
 *   RobotControl servos, dc motors, steppers 
 * ---------------------------------------------
 *
 * Uses the Arduino Serial library
 *  (http://arduino.cc/en/Reference/Serial)
 * and the Arduino Servo library
 *  (http://arduino.cc/en/Reference/Servo)
 * and the Arduino Stepper library
 *  (http://arduino.cc/en/Reference/Stepper)
 * to control multiple motors from a PC using a USB cable.
 *
 * Dependencies:
 *   Arduino 0017 or higher
 *     (http://www.arduino.cc/en/Main/Software)
 *   Python pythonController.py module
 *     (github...)
 *
 * Created:  30 January 2015
 * Author:   Garrett Kaiser
 * 
 * Version:  
 * License:  GPLv3
 *   (http://www.fsf.org/licensing/)
 *
 */

//Import Dynamixel Library
// uses RX3, TX3, and pin 2 on arduino mega
#include <DynamixelSerial3.h>

// Import the Arduino Servo and Stepper library
#include <Servo.h> 
#include <Stepper.h>

/*
// change this to the number of steps on your Steppermotor
#define STEPS_PER_MOTOR_REVOLUTION 32
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64  //2048
#define MAX_EXTENSION 2048 * 10
#define STEPPER_SPEED 700
*/

#define MAX_STEPS 72000

int minPulse = 600;   // minimum servo position, us (microseconds)
int maxPulse = 2400;  // maximum servo position, us


// Create a Servo object for each servo
Servo servo1;
//Servo servo2;

// TO ADD SERVOS:
//   Servo servo3;
//   etc...

// DC motor pins for each motor
int direction_pin_motorL[] = {48, 49};  // digital pins 
int speed_pin_motorL = 5;  // pwm pins
int direction_pin_motorR[] = {50, 51}; 
int speed_pin_motorR = 3;


// Create a Stepper object for each Steppermotor
//Stepper stepper1(STEPS_PER_MOTOR_REVOLUTION, 40, 41, 42, 43); // digital pins
int direction_pin_stepper = 40;
int step_pin_stepper = 41;




// servo variables
int servo;           
int pos;   
int realpos;

// dc-motor variables
int motor;
int motorDirection;
int motorSpeed;

// stepper variables
int stepper;
int ext;
int next;
int prev;
int steps;


int startCmd;
int userInput[3];    // raw input from serial buffer, 3 bytes max


void setup(){
  // initialize servo pins
  servo1.attach(9, minPulse, maxPulse); // pwm pins
  //servo2.attach(10, minPulse, maxPulse);
  
  Dynamixel.begin(1000000,2);  // Inicialize the servo at 1Mbps and Pin Control 2
  
  // initialize motor pins
  for(int i=0; i < 2; i++ ){  
     pinMode(direction_pin_motorL[i], OUTPUT);  
     pinMode(direction_pin_motorR[i], OUTPUT);  
  }  
  pinMode(5, OUTPUT);  
  pinMode(3, OUTPUT);
/* 
  // initialize stepper pinmodes
  pinMode(40, OUTPUT);
  pinMode(41,OUTPUT);
  pinMode(42,OUTPUT);
  pinMode(43,OUTPUT);
*/

  //initialize two pin control for stepper
  pinMode(40, OUTPUT); // direction control
  pinMode(41,OUTPUT); // step control

// setting initial position and speeds
  //stepper1.setSpeed(STEPPER_SPEED);
  prev = 0;
  next = 0;
  
  servo1.write(90);
  //servo2.write(45);
  
  digitalWrite(direction_pin_motorL[1], HIGH);  
  digitalWrite(direction_pin_motorL[0], LOW);
  analogWrite(speed_pin_motorL, 0);
  
  digitalWrite(direction_pin_motorR[1], HIGH);  
  digitalWrite(direction_pin_motorR[0], LOW);
  analogWrite(speed_pin_motorR, 0);
   
  
  Serial.begin(9600);
  delay(1000);
}

void loop(){
  delay(100);
  if(Serial.available() > 0) {
        startCmd = Serial.read();
        Serial.println(startCmd);
               
        switch ( startCmd ) {
            /*
              case 'g':
                    for (int i=0;i<2;i++) {
                       userInput[i] = (int) Serial.read();
                    }
                    // First byte = servo to move?
                    servo = userInput[0];
                    // Second byte = which position?
                    pos = constrain(userInput[1],0,180);
                    // Packet error checking and recovery
                    //if (pos == 255) { servo = 255; }
                    
                    // Assign new position to appropriate servo
                    switch (servo) {
                        case 1:
                          servo1.write(pos);    // move servo1 to 'pos'
                          break;
                        case 2:
                          servo2.write(pos);
                          break;
                    }
                    break;
             */
              
              case 'e':
                    Serial.println("case e");
                    for (int i=0; i< 1; i++){
                        userInput[i] = (int) Serial.read();
                    }
                    pos = constrain(userInput[0],0,243);
                    realpos = 1023 - pos;
                    Dynamixel.move(1,realpos);
                    break;
                    
              case 'r':
                    Serial.println("case r");
                    for (int i=0; i< 1; i++){
                        userInput[i] = (int) Serial.read();
                    }
                    pos = constrain(userInput[0],0,180);
                    
                    servo1.write(pos);
                    break;
                    
              case 'x':
                    Serial.println("case x");
                    for (int i=0; i< 1; i++){
                        userInput[i] = (int) Serial.read();
                    }
                    ext = constrain(userInput[0],0,20);
                    next = MAX_STEPS * (ext/20);
                    if (next > prev){
                        digitalWrite(direction_pin_stepper, HIGH);
                        while (next > prev){
                            digitalWrite(step_pin_stepper, HIGH);
                            delay(1);
                            digitalWrite(step_pin_stepper, LOW);
                            
                            next = next - 1;
                        }
                    }
                    else if (next < prev){
                        digitalWrite(direction_pin_stepper, LOW);
                        while (next < prev){
                            digitalWrite(step_pin_stepper, HIGH);
                            delay(1);
                            digitalWrite(step_pin_stepper, LOW);
                            
                            next = next + 1;
                        }
                    }
                    break;
                    
              case 'g':
                    Serial.println("case g");
                    for (int i=0; i< 1; i++){
                        userInput[i] = (int) Serial.read();
                    }
                    pos = constrain(userInput[0],0,173);
                    realpos = 1023 - pos;
                    Dynamixel.move(2,realpos);
                    break;
                    
              case 'w':
                    Serial.println("case w");
                    for (int i=0;i<3;i++) {
                        userInput[i] = Serial.read();
                    }
                    
                    motor = userInput[0];
                    motorDirection = userInput[1];
                    motorSpeed = userInput[2];
                    
                    Serial.println(motorSpeed);
                    
                    switch (motor) {
                        case 1:
                            if (motorDirection == 'f') {
                                digitalWrite(direction_pin_motorL[1], HIGH);  
                                digitalWrite(direction_pin_motorL[0], LOW);
                                Serial.println("motor 1 f");
                            }
                            else if (motorDirection == 'r') {
                                digitalWrite(direction_pin_motorL[1], LOW);  
                                digitalWrite(direction_pin_motorL[0], HIGH);
                                Serial.println("motor 1 r");
                            }
                            else {
                                // motor direction invalid 
                            }  
                          Serial.println("updating speed");  
                            analogWrite(speed_pin_motorL, motorSpeed);
                            break;
                        case 2:
                            if (motorDirection == 'f') {
                                digitalWrite(direction_pin_motorR[1], HIGH);  
                                digitalWrite(direction_pin_motorR[0], LOW); 
                                Serial.println("motor 2 f");
                            }
                            else if (motorDirection == 'r') {
                                digitalWrite(direction_pin_motorR[1], LOW);  
                                digitalWrite(direction_pin_motorR[0], HIGH);
                                Serial.println("motor 2 r");
                            }
                            else {
                                //motor direction invalid
                            } 
                            analogWrite(speed_pin_motorR, motorSpeed);
                            break;
                    }
                    break;
                    
              case 'b':
                    Serial.println("case b");
                    for (int i=0;i<2;i++) {
                        userInput[i] = Serial.read();
                    }
                    
                    motorDirection = userInput[0];
                    motorSpeed = userInput[1];
                    
                    Serial.println(motorSpeed);
                    

                    if (motorDirection == 'f') {
                        digitalWrite(direction_pin_motorL[1], HIGH);  
                        digitalWrite(direction_pin_motorL[0], LOW);
                        Serial.println("motor 1 f");
                        digitalWrite(direction_pin_motorR[1], HIGH);  
                        digitalWrite(direction_pin_motorR[0], LOW); 
                        Serial.println("motor 2 f");
                    }
                    else if (motorDirection == 'r') {
                        digitalWrite(direction_pin_motorL[1], LOW);  
                        digitalWrite(direction_pin_motorL[0], HIGH);
                        Serial.println("motor 1 r");
                        digitalWrite(direction_pin_motorR[1], LOW);  
                        digitalWrite(direction_pin_motorR[0], HIGH);
                        Serial.println("motor 2 r");
                    }
                    else {
                        // motor direction invalid 
                    }  
                    Serial.println("updating speed");  
                    analogWrite(speed_pin_motorL, motorSpeed);
                    analogWrite(speed_pin_motorR, motorSpeed);
                    break;
              
              
              /*
              case 'k':
                    for (int i=0;i<2;i++) {
                      userInput[i] = Serial.read();
                    }
                    
                    stepper = userInput[0];
                    ext = userInput[1];
                    
                    switch(stepper) {
                        case 1:
                          next = MAX_EXTENSION * (ext/10);
                          steps = next - prev;
                          stepper1.step(steps);
                          prev = next;
                          break;
                    }
                    break;
              */
                    
              default:
                    Serial.println("error no command");
                    break;
        }
  }
  delay(100);
   
}
