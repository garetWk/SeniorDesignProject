

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
 *   Arduino Mega 2560
 *     (http://www.arduino.cc/en/Main/Software)
 *   Python pythonController.py module old control method
 *     (github...)
 *   RoBoeServer.py
 *   RoBoe GUI
 *
 * Updated:  Marh 26 2015
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


int minPulse = 600;   // minimum servo position, us (microseconds)
int maxPulse = 2400;  // maximum servo position, us


// Create a Servo object for each servo
Servo servo1;

// TO ADD SERVOS:
//   Servo servo2;
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
double next;
double prev;
int steps;
int diff;
float frac;


int inputByte_0;
int inputByte_1;
int inputByte_2;
int inputByte_3;
int inputByte_4;
int inputByte_5;


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

  //initialize two pin control for stepper
  pinMode(40, OUTPUT); // direction control
  pinMode(41,OUTPUT); // step control

// setting initial position and speeds
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
   
  
  Serial.begin(115200);
  Serial.flush();
  delay(1000);
}

void loop(){
  if(Serial.available() >= 6) {
       //Read buffer
      inputByte_0 = (int) Serial.read();
        
      inputByte_1 = (int) Serial.read();
         
      inputByte_2 = (int) Serial.read();
          
      inputByte_3 = (int) Serial.read();
    
      inputByte_4 = (int) Serial.read(); 
    
      inputByte_5 = (int)  Serial.read();
      
      if(inputByte_0 == 16) {          
          switch ( inputByte_1 ) {
                  
                  case 'e':
                        //Serial.println("case e");
                        
                        pos = constrain(inputByte_2,0,243);
                        realpos = 1023 - pos;
                        Dynamixel.move(1,realpos);
                        break;
                        
                  case 'r':
                        //Serial.println("case r");
                        
                        pos = constrain(inputByte_2,0,180);
                        
                        servo1.write(pos);
                        break;
                        
                  case 'x':
                        //Serial.println("case x");
                        
                        //ext = inputByte_2;
                        //Serial.println(ext);
                        
                        frac = (float(inputByte_2) / float(10));
                                  
                        next = (28800 * (frac));
                        Serial.println(next);
                        Serial.println(prev);
                        
                        if (next > prev){
                            digitalWrite(direction_pin_stepper, LOW);
                            while (next > prev){
                                digitalWrite(step_pin_stepper, HIGH);
                                delayMicroseconds(800);
                                digitalWrite(step_pin_stepper, LOW);
                                delayMicroseconds(800);
                                
                                prev = prev + 1;
                            }
                            Serial.println("finished moving");
                        }
                        else if (next < prev){
                            digitalWrite(direction_pin_stepper, HIGH);
                            while (next < prev){
                                digitalWrite(step_pin_stepper, HIGH);
                                delayMicroseconds(800);
                                digitalWrite(step_pin_stepper, LOW);
                                delayMicroseconds(800);
                                
                                prev = prev - 1;
                            }
                            Serial.println("finished moving");
                        }
                        
                        break;
                        
                  case 'g':
                        //Serial.println("case g");
                        
                        pos = constrain(inputByte_2,0,173);
                        realpos = 1023 - pos;
                        Dynamixel.move(2,realpos);
                        break;
                        
                  case 'w':
                        //Serial.println("case w");
                        
                        motor = inputByte_2;
                        motorDirection = inputByte_3;
                        motorSpeed = inputByte_4;
                        
                        switch (motor) {
                            case 1:
                                if (motorDirection == 'f') {
                                    digitalWrite(direction_pin_motorL[1], HIGH);  
                                    digitalWrite(direction_pin_motorL[0], LOW);
                                    //Serial.println("motor 1 f");
                                }
                                else if (motorDirection == 'r') {
                                    digitalWrite(direction_pin_motorL[1], LOW);  
                                    digitalWrite(direction_pin_motorL[0], HIGH);
                                    //Serial.println("motor 1 r");
                                }
                                else {
                                    // motor direction invalid 
                                }  
                              //Serial.println("updating speed");  
                                analogWrite(speed_pin_motorL, motorSpeed);
                                break;
                            case 2:
                                if (motorDirection == 'f') {
                                    digitalWrite(direction_pin_motorR[1], HIGH);  
                                    digitalWrite(direction_pin_motorR[0], LOW); 
                                    //Serial.println("motor 2 f");
                                }
                                else if (motorDirection == 'r') {
                                    digitalWrite(direction_pin_motorR[1], LOW);  
                                    digitalWrite(direction_pin_motorR[0], HIGH);
                                    //Serial.println("motor 2 r");
                                }
                                else {
                                    //motor direction invalid
                                } 
                                analogWrite(speed_pin_motorR, motorSpeed);
                                break;
                        }
                        break;
                        
                  case 'b':
                        //Serial.println("case b");
                        
                        motorDirection = inputByte_2;
                        motorSpeed = inputByte_3;
      
                        if (motorDirection == 'f') {
                            digitalWrite(direction_pin_motorL[1], HIGH);  
                            digitalWrite(direction_pin_motorL[0], LOW);
                            //Serial.println("motor 1 f");
                            digitalWrite(direction_pin_motorR[1], HIGH);  
                            digitalWrite(direction_pin_motorR[0], LOW); 
                            //Serial.println("motor 2 f");
                        }
                        else if (motorDirection == 'r') {
                            digitalWrite(direction_pin_motorL[1], LOW);  
                            digitalWrite(direction_pin_motorL[0], HIGH);
                            //Serial.println("motor 1 r");
                            digitalWrite(direction_pin_motorR[1], LOW);  
                            digitalWrite(direction_pin_motorR[0], HIGH);
                            //Serial.println("motor 2 r");
                        }
                        else {
                            // motor direction invalid 
                        }  
                        //Serial.println("updating speed");  
                        analogWrite(speed_pin_motorL, motorSpeed);
                        analogWrite(speed_pin_motorR, motorSpeed);
                        break;
                        
                  default:
                        Serial.println("error no command");
                        break;
            }  
      }
      else{
        Serial.println("first byte not 16 error");
      }
      
      inputByte_0 = 0;
      inputByte_1 = 0;
      inputByte_2 = 0;
      inputByte_3 = 0;
      inputByte_4 = 0;
      inputByte_5 = 0;
  }
   
}
