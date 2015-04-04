from socket import *
import ssl
import pprint
from time import gmtime
import serial
from os import system

import struct

import select

serverIP = '192.168.0.100'
serverPort = 50008

usbport = '/dev/tty.usbmodemfa131'

#ser = serial.Serial(usbport,115200,timeout=None)



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

    inputs = [ serverTCP ]
    outputs = [ ]
    
    while inputs:
        readable, writeable, exceptional = select.select(inputs, outputs, inputs)

        for s in exceptional:
            print('handling exceptional condition for ', s.getpeername())
            inputs.remove(s)
            if s in outputs:
                outputs.remove(s)
            s.close()

        for s in readable:
            if s is serverTCP:
                try:
                    connection, address = s.accept()
                    print('Server connected by', address,'at', gmtime())
                    inputs.append(connection)
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
            else:
                msg = s.recv(11).decode()
                if msg:
                    print(msg)
                    msg = msg.split('-')
                    #print(msg)
                    '''
                    if msg[0] == 'e':
                        ser.write(chr(16))
                        ser.write('e')
                        ser.write(chr(int(msg[1])))
                        ser.write(chr(4))
                        ser.write(chr(4))
                        ser.write(chr(4))
                        print("done elevation")

                    
                    if msg[0] == 'r':
                        ser.write(chr(16))
                        ser.write('r')
                        ser.write(chr(int(msg[1])))
                        ser.write(chr(4))
                        ser.write(chr(4))
                        ser.write(chr(4))

                    if msg[0] == 'x':
                        ser.write(chr(16))
                        ser.write('x')
                        ser.write(chr(int(msg[1])))
                        ser.write(chr(4))
                        ser.write(chr(4))
                        ser.write(chr(4))
                        
                        

                    if msg[0] == 'g':
                        ser.write(chr(16))
                        ser.write('g')
                        ser.write(chr(int(msg[1])))
                        ser.write(chr(4))
                        ser.write(chr(4))
                        ser.write(chr(4))

                    if msg[0] == 'w':
                        ser.write(chr(16))
                        ser.write('w')
                        ser.write(chr(int(msg[1])))
                        if msg[2] == 'f':
                            ser.write('f')
                        elif msg[2] == 'r':
                            ser.write('r')
                        ser.write(chr(int(msg[3])))
                        ser.write(chr(4))
                        

                    if msg[0] == 'b':
                        ser.write(chr(16))
                        ser.write('b')
                        if msg[1] == 'f':
                            ser.write('f')
                        elif msg[1] == 'r':
                            ser.write('r')
                        ser.write(chr(int(msg[2])))
                        ser.write(chr(4))
                        ser.write(chr(4))
                    '''
                   
                else:
                    print('closing connection ', address)
                    if s in outputs:
                        outputs.remove(s)
                    inputs.remove(s)
                    s.close()
                
            
            
                
                
                          
                          
