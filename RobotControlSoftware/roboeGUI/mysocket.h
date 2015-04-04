#ifndef MYSOCKET_H
#define MYSOCKET_H

#include <QObject>
#include <QTcpSocket>

class MySocket : public QObject
{
    Q_OBJECT
public:
    explicit MySocket(QObject *parent = 0);
    ~MySocket();

signals:

public slots:
    void connect(QString host, QString port);

    void writeMotorL(int value);
    void writeMotorR(int value);
    void writeMotorLR(int value);

    void writeElevation(int value);
    void writeRotation(int value);
    void writeExtend(int value);
    void writeGrip(int value);


private:
    QTcpSocket *socket;
    int previousValue;
};

#endif // MYSOCKET_H
