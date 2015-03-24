#include "mysocket.h"

#include <string>
#include <iostream>
#include <sstream>
using namespace std;

MySocket::MySocket(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
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
    if(value >= 0){
        ss << 'w' << '-' << '1' << '-' << 'f' << '-' << value;
        msg = ss.str();
    }
    else{
        value = value * -1;
        ss << 'w' << '-' << '1' << '-' << 'r' << '-' << value;
        msg = ss.str();
    }


    socket->write(msg.c_str());
}

void MySocket::writeMotorR(int value)
{
    string msg;
    stringstream ss;
    if(value >= 0){
        ss << 'w' << '-' << '2' << '-' << 'f' << '-' << value;
        msg = ss.str();
    }
    else{
        value = value * -1;
        ss << 'w' << '-' << '2' << '-' << 'r' << '-' << value;
        msg = ss.str();
    }

    socket->write(msg.c_str());
}

void MySocket::writeMotorLR(int value)
{
    string msg;
    stringstream ss;
    if(value >= 0){
        ss << 'b' << '-' << 'f' << '-' << value;
        msg = ss.str();
    }
    else{
        value = value * -1;
        ss << 'b' << '-' << 'r' << '-' << value;
        msg = ss.str();
    }

    socket->write(msg.c_str());
}

void MySocket::writeServo(int id, int value)
{
    string msg;
    stringstream ss;

    ss << 'g' << '-' << id << '-' << value;
    msg = ss.str();

    socket->write(msg.c_str());
}

void MySocket::writeElevation(int value){
    string msg;
    stringstream ss;

    ss << 'e' << '-' << value;
    msg = ss.str();

    socket->write(msg.c_str());
}

void MySocket::writeRotation(int value){
    string msg;
    stringstream ss;

    ss << 'r' << '-' << value;
    msg = ss.str();

    socket->write(msg.c_str());
}

void MySocket::writeExtend(int value){
    string msg;
    stringstream ss;

    ss << 'x' << '-' << value;
    msg = ss.str();

    socket->write(msg.c_str());
}

void MySocket::writeGrip(int value){
    string msg;
    stringstream ss;

    ss << 'g' << '-' << value;
    msg = ss.str();

    socket->write(msg.c_str());
}

