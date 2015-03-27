

/*
 * ---------------------------------------------
 *   RobotControl servos, dc motors, steppers 
 * ---------------------------------------------
 *
 * Uses the Arduino Serial library
 *  (http://arduino.cc/en/Reference/Serial)
 * Dependencies:
 *   Arduino Mega 2560
 *     (http://www.arduino.cc/en/Main/Software)
 *   RoBoeServer.py
 *   RoBoe GUI
 *
 * Updated:  March 27 2015
 * Author:   Garrett Kaiser
 * 
 * Version:  
 * License:  GPLv3
 *   (http://www.fsf.org/licensing/)
 *
 */


// servo variables          
int pos;   
int realpos;

// dc-motor variables
int motor;
int motorDirection;
int motorSpeed;

// stepper variables
int ext;
double next;
double prev;
float frac;


int startCmd;
int userInput[3];    // raw input from serial buffer, 3 bytes max

int inputByte_0;
int inputByte_1;
int inputByte_2;
int inputByte_3;
int inputByte_4;
int inputByte_5;


void setup(){
  
// setting initial position and speeds
  prev = 0;
  next = 0;
  
  
  Serial.begin(115200);
  Serial.flush();
  delay(1000); 
}

void loop(){
  if(Serial.available() >= 6) 
  {
    //Read buffer
    inputByte_0 = (int) Serial.read();
    //delay(100);    
    inputByte_1 = (int) Serial.read();
    //delay(100);      
    inputByte_2 = (int) Serial.read();
    //delay(100);      
    inputByte_3 = (int) Serial.read();
    //delay(100);
    inputByte_4 = (int) Serial.read(); 
    
    inputByte_5 = (int)  Serial.read();
     
   
   
    if(inputByte_0 == 16)
    {
      Serial.print(inputByte_0);
      Serial.print(" ");
      Serial.print(inputByte_1);
      Serial.print(" ");
      Serial.print(inputByte_2);
      Serial.print(" ");
      Serial.print(inputByte_3);
      Serial.print(" ");
      Serial.print(inputByte_4);
      Serial.print(" ");
      Serial.print(inputByte_5);
      Serial.println();
    } 
    else{
      Serial.println("fist bytte not 16");
    }
    
    
    switch ( inputByte_1 ) {
      
              case 'e':
                    //Serial.println("case e");
                    
                    pos = constrain(inputByte_2,0,243);
                    realpos = 1023 - pos;
                    Serial.print(realpos);
                    Serial.println();
                    break;
                    
              case 'r':
                    //Serial.println("case r");
                    
                    pos = constrain(inputByte_2,0,180);
                    
                    Serial.print(pos);
                    Serial.println();
                    break;
                    
              case 'x':
                    //Serial.println("case x");
                    
                    //ext = inputByte_2;
                    //Serial.println(ext);
                    
                    frac = (float(inputByte_2) / float(10));
                              
                    next = (28800 * (frac));
                    Serial.print("next: ");
                    Serial.print(next);
                    Serial.print("prev: ");
                    Serial.print(prev);
                    
                    if (next > prev){
                        Serial.print(" direction out");
                        while (next > prev){
                            prev = prev + 1;
                        }
                        Serial.print(" finished moving");
                        Serial.println();
                        
                    }
                    else if (next < prev){
                        Serial.print(" direction in");
                        while (next < prev){
                            prev = prev - 1;
                        }
                        Serial.print(" finished moving");
                        Serial.println();   
                    }
                    break;
                    
              case 'g':
                    //Serial.println("case g");
                    
                    pos = constrain(inputByte_2,0,173);
                    realpos = 1023 - pos;
                    Serial.print(realpos);
                    Serial.println();
                    break;
                    
              case 'w':
                    //Serial.println("case w");
                    
                    motor = inputByte_2;
                    motorDirection = inputByte_3;
                    motorSpeed = inputByte_4;
                    
                    switch (motor) {
                        case 1:
                            if (motorDirection == 'f') {
                                Serial.print("motor 1 f ");
                            }
                            else if (motorDirection == 'r') {
                                Serial.print("motor 1 r ");
                            }
                            else {
                                // motor direction invalid 
                            }  
                            Serial.print("updating speed: ");  
                            Serial.print(motorSpeed);
                            Serial.println();
                            break;
                        case 2:
                            if (motorDirection == 'f') { 
                                Serial.print("motor 2 f ");
                            }
                            else if (motorDirection == 'r') {
                                Serial.print("motor 2 r ");
                            }
                            else {
                                //motor direction invalid
                            } 
                            Serial.print("updating speed: ");
                            Serial.print(motorSpeed);
                            Serial.println();
                            break;
                    }
                    break;
                    
              case 'b':
                    //Serial.println("case b");
                    
                    motorDirection = inputByte_2;
                    motorSpeed = inputByte_3;
                    
                    if (motorDirection == 'f') {
                        Serial.print("both motors f ");
                    }
                    else if (motorDirection == 'r') {
                        Serial.print("both motors r ");
                    }
                    else {
                        // motor direction invalid 
                    }  
                    Serial.print("updating speed: ");  
                    Serial.print(motorSpeed);
                    Serial.println();
                    break;
                    
              default:
                    Serial.println("error no command");
                    break;
        }
    inputByte_0 = 0;
    inputByte_1 = 0;
    inputByte_2 = 0;
    inputByte_3 = 0;
    inputByte_4 = 0;
    inputByte_5 = 0;
  }
   
}
