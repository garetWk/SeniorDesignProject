from socket import *
import ssl
import pprint
from time import gmtime
import serial
from os import system

import select

serverIP = '127.0.0.1'
serverPort = 50007

usbport = '/dev/ttyACM0'



if __name__ == '__main__':
    serverTCP = socket(AF_INET, SOCK_STREAM)
    serverTCP.bind((serverIP,serverPort))
    serverTCP.listen(1)

    serverUDP = socket(AF_INET, SOCK_DGRAM)
    
    print("started")

    #serial = serial.Serial(usbport,9600,timeout=None)

    try:
        connection, address = serverTCP.accept()
        
        ssl_connection = ssl.wrap_socket(connection,
                                         server_side=True,
                                         certfile="server.crt",
                                         keyfile="server.key",
                                         ca_certs="client.crt",
                                         cert_reqs=ssl.CERT_REQUIRED)
        

    except Exception as e:
        log = open("log.txt", 'a')
        msg = '\n' + 'SSL Error on ' + now() + ' by ' + address + '\n'
        log.write(msg)
        log.write(str(e))
        log.write('\n')
        log.close()
        raise e

    
    print (repr(ssl_connection.getpeername()))
    print (ssl_connection.cipher())
    print (pprint.pformat(ssl_connection.getpeercert()))
    print('Server connected by', address,'at', gmtime())
    

    while True:
        try:
            ready_to_read, read_to_write, in_error = \
                           select.select([ssl_connection,], [ssl_connection,], [], 5)
        except select.error:
            ssl_connection.shutdown(2)
            ssl_connection.close()
            print("closed connection")

        if len(ready_to_read) > 0:
            
            msg = ssl_connection.recv(1024).decode().split("-")

            for element in msg:
                print(element)
                #serial.write(element)
            
