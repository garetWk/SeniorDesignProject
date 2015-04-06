#include "mysocket.h"

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

MySocket::MySocket(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    previousValue = 0;
}

MySocket::~MySocket()
{

}

void MySocket::connect(QString host, QString port)
{
    socket->connectToHost(host,port.toInt());
    //cout << "connected to host: " << host.toStdString() << endl;
}

void MySocket::writeMotorL(int value)
{
    string msg;
    stringstream ss;
    string filler;

    if(value >= 0){
        int length = value/10;
        cout<<length;
        if(length == 0){
            filler = "sss";
        }
        else if(length < 10){
            filler = "ss";
        }
        else if(length >= 10){
            filler="s";
        }
        ss << 'w' <<'-'<< '1' <<'-'<< 'f' <<'-'<< value <<'-'<< filler;
        msg = ss.str();
    }
    else{
        value = value * -1;
        int length = value/10;
        cout<<length;
        if(length == 0){
            filler = "sss";
        }
        else if(length < 10){
            filler = "ss";
        }
        else if(length >= 10){
            filler="s";
        }
        ss << 'w' <<'-'<< '1' <<'-'<< 'r' <<'-'<< value <<'-'<< filler;
        msg = ss.str();
    }

    socket->write(msg.c_str());
}

void MySocket::writeMotorR(int value)
{
    string msg;
    stringstream ss;
    string filler;

    if(value >= 0){
        int length = value/10;
        cout<<length;
        if(length == 0){
            filler = "sss";
        }
        else if(length < 10){
            filler = "ss";
        }
        else if(length >= 10){
            filler="s";
        }
        ss << 'w' <<'-'<< '2' <<'-'<< 'f' <<'-'<< value <<'-'<< filler;
        msg = ss.str();
    }
    else{
        value = value * -1;
        int length = value/10;
        cout<<length;
        if(length == 0){
            filler = "sss";
        }
        else if(length < 10){
            filler = "ss";
        }
        else if(length >= 10){
            filler="s";
        }
        ss << 'w' <<'-'<< '2' <<'-'<< 'r' <<'-'<< value <<'-'<< filler;
        msg = ss.str();
    }

    socket->write(msg.c_str());
}

void MySocket::writeMotorLR(int value)
{
    string msg;
    stringstream ss;
    string filler;

    if(value != previousValue)
    {
        previousValue = value;
        if(value >= 0){
            int length = value/10;
            cout<<length;
            if(length == 0){
                filler = "sssss";
            }
            else if(length < 10){
                filler = "ssss";
            }
            else if(length >= 10){
                filler="sss";
            }
            ss << 'b' <<'-'<< 'f' <<'-'<< value <<'-'<< filler;
            msg = ss.str();
        }
        else{
            value = value * -1;
            int length = value/10;
            cout<<length;
            if(length == 0){
                filler = "sssss";
            }
            else if(length < 10){
                filler = "ssss";
            }
            else if(length >= 10){
                filler="sss";
            }
            ss << 'b' <<'-'<< 'r' <<'-'<< value <<'-'<< filler;
            msg = ss.str();
        }

        socket->write(msg.c_str());
    }
}


void MySocket::writeElevation(int value){
    string msg;
    stringstream ss;
    string filler;

    int length = value/10;
    cout<<length;
    if(length == 0){
        filler = "sssssss";
    }
    else if(length < 10){
        filler = "ssssss";
    }
    else if(length >= 10){
        filler="sssss";
    }

    ss << 'e' <<'-'<< value <<'-'<< filler;
    msg = ss.str();

    socket->write(msg.c_str());
}

void MySocket::writeRotation(int value){
    string msg;
    stringstream ss;
    string filler;

    int length = value/10;
    cout<<length;
    if(length == 0){
        filler = "sssssss";
    }
    else if(length < 10){
        filler = "ssssss";
    }
    else if(length >= 10){
        filler="sssss";
    }

    ss << 'r' <<'-'<< value <<'-'<< filler;
    msg = ss.str();

    socket->write(msg.c_str());
}

void MySocket::writeExtend(int value){
    string msg;
    stringstream ss;
    string filler;

    int length = value/10;
    cout<< length;
    if(length == 0){
        filler = "sssssss";
    }
    else if(length < 10){
        filler = "ssssss";
    }
    else if(length >= 10){
        filler="sssss";
    }

    ss << 'x' <<'-'<< value <<'-'<< filler;
    msg = ss.str();

    socket->write(msg.c_str());
}

void MySocket::writeGrip(int value){
    string msg;
    stringstream ss;
    string filler;

    int length = value/10;
    cout<<length;
    if(length == 0){
        filler = "sssssss";
    }
    else if(length < 10){
        filler = "ssssss";
    }
    else if(length >= 10){
        filler="sssss";
    }

    ss << 'g' <<'-'<< value <<'-'<< filler;
    msg = ss.str();

    socket->write(msg.c_str());
}

