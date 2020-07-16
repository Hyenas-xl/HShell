#ifndef SERIALPORT_H
#define SERIALPORT_H

#include "baseport.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "config.h"

class SerialPort:public BasePort
{
    Q_OBJECT
public:
    SerialPort(SerialSetting *setting);

    QByteArray readAll();
    void write(const QByteArray &data);
    bool open(QIODevice::OpenMode mode);
    void close();

    bool isOpen();

public slots:
    void readyReadNow();
signals:
    void readyRead();

private:
    QSerialPort *mSerial = NULL;
};

#endif // SERIALPORT_H
