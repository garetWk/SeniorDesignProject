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



// Import the Arduino Servo and Stepper library
#include <Servo.h> 
#include <Stepper.h>

// change this to the number of steps on your Steppermotor
#define STEPS_PER_MOTOR_REVOLUTION 32
#define STEPS_PER_OUTPUT_REVOLUTION 32 * 64  //2048
#define MAX_EXTENSION 2048 * 10
#define STEPPER_SPEED 700

int minPulse = 600;   // minimum servo position, us (microseconds)
int maxPulse = 2400;  // maximum servo position, us



// Create a Servo object for each servo
Servo servo1;
Servo servo2;

// TO ADD SERVOS:
//   Servo servo3;
//   etc...

// DC motor pins for each motor
int direction_pin_motorL[] = {0, 6};  // digital pins 
int speed_pin_motorL = 5;  // pwm pins
int direction_pin_motorR[] = {50, 51}; 
int speed_pin_motorR = 1;

// Create a Stepper object for each Steppermotor
Stepper stepper1(STEPS_PER_MOTOR_REVOLUTION, 40, 41, 42, 43); // digital pins



// servo variables
int servo;           
int pos;             

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
  servo1.attach(9, minPulse, maxPulse); // pwm pins
  servo2.attach(10, minPulse, maxPulse);
  
  for(int i=0; i < 2; i++ ){  
     pinMode(direction_pin_motorL[i], OUTPUT);  
     pinMode(direction_pin_motorR[i], OUTPUT);  
  }  
  pinMode(5, OUTPUT);  
  pinMode(1, OUTPUT);
  
  // Stepper pinmodes
  pinMode(40, OUTPUT);
  pinMode(41,OUTPUT);
  pinMode(42,OUTPUT);
  pinMode(43,OUTPUT);

  stepper1.setSpeed(STEPPER_SPEED);
  prev = 0; 
  
  Serial.begin(9600);
}

void loop(){
        startCmd = Serial.read();
        Serial.println(startCmd);
               
        switch ( startCmd ) {
              case 'g':
                    for (int i=0;i<2;i++) {
                       userInput[i] = Serial.read();
                    }
                    // First byte = servo to move?
                    servo = userInput[0];
                    // Second byte = which position?
                    pos = userInput[1];
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
                    
              case 'w':
                    for (int i=0;i<3;i++) {
                        userInput[i] = Serial.read();
                    }
                    
                    motor = userInput[0];
                    motorDirection = userInput[1];
                    motorSpeed = userInput[2];
                    
                    switch (motor) {
                        case 1:
                            if (motorDirection == 'f') {
                                digitalWrite(direction_pin_motorL[1], HIGH);  
                                digitalWrite(direction_pin_motorL[0], LOW);
                                Serial.print("motor 1 f");
                            }
                            else if (motorDirection == 'r') {
                                digitalWrite(direction_pin_motorL[1], LOW);  
                                digitalWrite(direction_pin_motorL[0], HIGH);
                                Serial.print("motor 1 r");
                            }
                            else {
                                // motor direction invalid 
                            }    
                            analogWrite(speed_pin_motorL, motorSpeed);
                            break;
                        case 2:
                            if (motorDirection == 'f') {
                                digitalWrite(direction_pin_motorR[1], HIGH);  
                                digitalWrite(direction_pin_motorR[0], LOW); 
                                Serial.print("motor 2 f");
                            }
                            else if (motorDirection == 'r') {
                                digitalWrite(direction_pin_motorR[1], LOW);  
                                digitalWrite(direction_pin_motorR[0], HIGH);
                                Serial.print("motor 2 r");
                            }
                            else {
                                //motor direction invalid
                            } 
                            analogWrite(speed_pin_motorR, motorSpeed);
                            break;
                    }
              case 'k':
                    for (int i=0;i<2;i++) {
                      userInput[i] = Serial.read();
                    }
                    
                    stepper = userInput[0];
                    ext = userInput[1];
                    
                    
                    switch (stepper) {
                        case 1:
                            switch (ext) {
                                case 0:
                                    next = MAX_EXTENSION * 0;
                                    steps = next - prev;
                                    stepper1.step(steps);
                                    break;
                                case 1:
                                    next = MAX_EXTENSION * (1/10);
                                    steps = next - prev;
                                    stepper1.step(steps);
                                    break;
                                case 2:
                                    next = MAX_EXTENSION * (2/10);
                                    steps = next - prev;
                                    stepper1.step(steps);
                                    break;
                                case 3:
                                    next = MAX_EXTENSION * (3/10);
                                    steps = next - prev;
                                    stepper1.step(steps);
                                    break;
                                case 4:
                                    next = MAX_EXTENSION * (4/10);
                                    steps = next - prev;
                                    stepper1.step(steps);
                                    break;
                                case 5:
                                    next = MAX_EXTENSION * (5/10);
                                    steps = next - prev;
                                    stepper1.step(steps);
                                    break;
                                case 6:
                                    next = MAX_EXTENSION * (6/10);
                                    steps = next - prev;
                                    stepper1.step(steps);
                                case 7:
                                    next = MAX_EXTENSION * (7/10);
                                    steps = next - prev;
                                    stepper1.step(steps);
                                    break;
                                case 8:
                                    next = MAX_EXTENSION * (8/10);
                                    steps = next - prev;
                                    stepper1.step(steps);
                                    break;
                                case 9:
                                    next = MAX_EXTENSION * (9/10);
                                    steps = next - prev;
                                    stepper1.step(steps);
                                    break;
                                case 10:
                                    next = MAX_EXTENSION * (10/10);
                                    steps = next - prev;
                                    stepper1.step(steps);
                                    break;
                                default:
                                    // not mapped above 10
                                    break;
                            }
                            break;
                    }
                    
              default:
                    Serial.println("error no command");
        }
  
   
}
