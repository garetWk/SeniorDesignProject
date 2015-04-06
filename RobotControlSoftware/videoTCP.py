from socket import *
from socket import *
import ssl
import pprint
from time import gmtime
import serial
from os import system

import struct
import select



serverIP = '192.168.0.100'
serverPort = 50009


if __name__ == '__main__':
    videoTCP = socket(AF_INET, SOCK_STREAM)
    videoTCP.connect((serverIP,serverPort))

    file_name = "/dev/video0"
    f = open(file_name,"rb")

    data = f.read(1024)
    while(data):
        print("sending...")
        videoTCP.send(data)
        data = f.read(1024)

    videoTCP.close()
    f.close()
    
    
                
