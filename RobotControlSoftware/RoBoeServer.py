from socket import *
import ssl
import pprint
from time import gmtime
import serial
from os import system

import struct

import select

serverIP = '192.168.0.101'
serverPort = 50008

usbport = '/dev/tty.usbmodemfa131'

#ser = serial.Serial(usbport,9600,timeout=None)



'''
from functools import wraps

def sslwrap(func):
    @wraps(func)
    def bar(*args, **kw):
        kw['ssl_version'] = ssl.PROTOCOL_TLSv1
        return func(*args, **kw)
    return bar
'''



if __name__ == '__main__':
    serverTCP = socket(AF_INET, SOCK_STREAM)
    serverTCP.bind((serverIP,serverPort))
    serverTCP.listen(1)

    serverUDP = socket(AF_INET, SOCK_DGRAM)
    
    print("started")
    print("at host: " + str(serverIP) + "port: " + str(serverPort))

    try:
        connection, address = serverTCP.accept()
        '''
        ssl_connection = ssl.wrap_socket(connection,
                                         keyfile="server.key",
                                         certfile="server.crt",
                                         server_side=True,
                                         cert_reqs=ssl.CERT_NONE,
                                         ssl_version=ssl.PROTOCOL_SSLv23,
                                         ca_certs="client.crt",
                                         do_handshake_on_connect=True,
                                         suppress_ragged_eofs=True,
                                         ciphers=None)
        '''

    except Exception as e:
        log = open("log.txt", 'a')
        #msg = '\n' + 'SSL Error on ' + str(gmtime()) + ' by ' + address + '\n'
        #log.write(msg)
        log.write(str(e))
        log.write('\n')
        log.close()
        raise e

    '''
    print (repr(ssl_connection.getpeername()))
    print (ssl_connection.cipher())
    print (pprint.pformat(ssl_connection.getpeercert()))
    '''
    print('Server connected by', address,'at', gmtime())
    

    while True:
        try:
            ready_to_read, read_to_write, in_error = \
                           select.select([connection,], [connection,], [], 5)
        except select.error:
            connection.shutdown(2)
            connection.close()
            print("closed connection")

        if len(ready_to_read) > 0:
            
            msg = connection.recv(11).decode()
            print(msg)
            msg = msg.split('-')
            print(msg)


            if msg[0] == 'e':
                ser.write('e')
                ser.write(chr(int(msg[1])))

            
            if msg[0] == 'r':
                ser.write('r')
                ser.write(chr(int(msg[1])))

            if msg[0] == 'x':
                ser.write('x')
                ser.write(chr(int(msg[1])))
                

            if msg[0] == 'g':
                ser.write('g')
                ser.write(chr(int(msg[1])))

            if msg[0] == 'w':
                ser.write('w')
                ser.write(chr(int(msg[1])))
                if msg[2] == 'f':
                    ser.write('f')
                elif msg[2] == 'r':
                    ser.write('r')
                ser.write(chr(int(msg[3])))

            if msg[0] == 'b':
                ser.write('b')
                if msg[1] == 'f':
                    ser.write('f')
                elif msg[1] == 'r':
                    ser.write('r')
                ser.write(chr(int(msg[2])))              

            
                
            
            
                
                
                          
                          
