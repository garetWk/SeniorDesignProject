from socket import *
import ssl
import pprint
import time
import serial
from os import system

serverIP = '127.0.0.1'
serverPort = 50007


clientTCP = socket(AF_INET, SOCK_STREAM)
clientUDP = socket(AF_INET, SOCK_DGRAM)

try:
    
    ssl_TCP = ssl.wrap_socket(clientTCP,
                              certfile="client.crt",
                              keyfile="client.key",
                              ca_certs="server.crt",
                              cert_reqs=ssl.CERT_NONE)
    ssl_TCP.connect((serverIP, serverPort))
    

except Exception as e:
    log = open("log.txt", 'a')
    log.write(str(e))
    log.write('\n')
    log.close()
    raise e


print (repr(ssl_TCP.getpeername()))
print (ssl_TCP.cipher())
print (pprint.pformat(ssl_TCP.getpeercert()))
print('client is connected')



def servo(servo, angle):
    msg = 'g' + "-" + str(servo) + "-" + str(angle)
    print(msg)
    ssl_TCP.send(msg.encode())


def dcmotor(motor, direction, speed):
    msg = 'w' + "-" + str(motor) + "-" + direction + "-" + str(speed)
    print(msg)
    ssl_TCP.send(msg.encode())


def stepper(stepper, ext):
    msg = 'k' + "-" + str(stepper) + "-" + str(ext)
    print(msg)
    ssl_TCP.send(msg.encode())
    


def forward(speed):
    msg = 'f' + "-" + str(speed)
    print(msg)
    ssl_TCP.send(msg.encode())

def reverse(speed):
    msg = 'r' + "-" + str(speed)
    print(msg)
    ssl_TCP.send(msg.encode())

def turn(direction, speed):
    msg = 't' + "-" + direction + "-" + str(speed)
    print(msg)
    ssl_TCP.send(msg.encode())
    
def stop():
    msg = 's'
    print(msg)
    ssl_TCP.send(msg.encode())


def close():
    ssl_TCP.close()
