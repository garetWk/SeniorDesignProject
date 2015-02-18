#!/usr/bin/env python

################################################
# Module:   pythonController.py
# Created:  30 January 2015
# Author:   Garrett Kaiser
#
# Version:  
# License:  GPLv3
#   http://www.fsf.org/licensing/
'''
Provides a serial connection abstraction layer
for use with Arduino "RobotControl" sketch.
'''
################################################

import serial
from os import system

# Assign Arduino's serial port address
#   Windows example
#     usbport = 'COM3'
#   Linux example
#     usbport = '/dev/ttyUSB0'
#   MacOSX example
#     usbport = '/dev/tty.usbserial-FTALLOK2'

usbport = '/dev/tty.usbmodemfa131'

# Set up serial baud rate
ser = serial.Serial(usbport,9600,timeout=None)

def servo(servo, angle):
   '''Moves the specified servo to the supplied angle.

    Arguments:
        servo
          the servo number to command, an integer from 1-2
        angle
          the desired servo angle, an integer from 0 to 180

    (e.g.) >>> servo(2, 90)
           ... # move servo #2 to 90 degrees '''
   if (0 <= angle <= 180):
      ser.write('g')
      ser.write(chr(servo))
      ser.write(chr(angle))
      
      '''system("echo 'g' > /dev/ttyACM0")
      cmd = "echo " + str(servo) + " > /dev/ttyACM0"
      print(cmd)
      system(cmd)
      cmd = "echo " + str(angle) + " > /dev/ttyACM0"
      print(cmd)
      system(cmd)'''
   else:
      print("Servo angle must be an integer between 0 and 180.\n")


def dcmotor(motor, direction, speed):
    '''Moves the specified DCmotor to the given speed and direction.

    Arguments:
        motor
          the motor number to command, an integer from 1-2
        direction
          the desired motor direction, an char 'f':forward or 'r':reverse
        speed
          the desired motor speed, an integer from 0-255

    (e.g.) >>> dcmotor(1,'f',100)
           ... # move DCmotor #1 at a speed 100 forward '''

    if( direction == 'f' or direction == 'r' ):
        if(0 <= speed <= 255):
            ser.write('w')
            ser.write(chr(motor))
            ser.write(direction)
            ser.write(chr(speed))           
        else:
            print("motor speed must be an integer between 0 and 255.\n")

    else:
        print("motor direction must be f or r .\n")


def stepper(stepper, ext):
   '''Moves the specified stepper to the given fraction of the MAX_STEPS.

    Arguments:
        stepper
          the stepper number to command, an integer
        ext
          the fraction of MAX_STEPS to take, an integer from 0-10 where 1->1/10 ... 10->10/10

    (e.g.) >>> stepper(1,5)
           ... # stepper one takes half the MAX_STEPS '''

   if(0 <= ext <= 10):
      ser.write('k')
      ser.write(chr(stepper))
      ser.write(chr(ext))
   else:
      print("ext must be an integer from 1 to 10. \n")
    









