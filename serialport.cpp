#include "serialport.h"
#include <QDebug>

SerialPort::SerialPort(SerialSetting *setting)
{
    mSerial = new QSerialPort;
    mSerial->setPortName(setting->portName);
    mSerial->setBaudRate(setting->baudRate);
    mSerial->setDataBits(setting->dataBit);
    mSerial->setParity(setting->parity);
    mSerial->setStopBits(setting->stopBits);
    mSerial->setFlowControl(setting->flowControl);

    connect(mSerial,&QSerialPort::readyRead,this,&SerialPort::readyReadNow);
}

bool SerialPort::open(QIODevice::OpenMode mode){
    if(mSerial != NULL){
        if(mSerial->isOpen()){
            return true;
        }
        qDebug() << "Serial Port open" << mode;
        qDebug() << mSerial->portName();
        qDebug() << mSerial->baudRate();
        qDebug() << mSerial->dataBits();
        qDebug() << mSerial->parity();
        qDebug() << mSerial->stopBits();
        qDebug() << mSerial->flowControl();

        return mSerial->open(mode);
    }
    return false;
}

void SerialPort::close(){
    if(mSerial != NULL && mSerial->isOpen()){
        mSerial->close();
        delete mSerial;
        mSerial = NULL;
    }
}

QByteArray SerialPort::readAll(){
    if(mSerial != NULL && mSerial->isOpen()){
        return mSerial->readAll();
    }
    QByteArray empty;
    return empty;
}

void SerialPort::write(const QByteArray &data){
    if(mSerial != NULL && mSerial->isOpen()){
        mSerial->write(data);
    }
}

bool SerialPort::isOpen(){
    if(mSerial != NULL){
        return mSerial->isOpen();
    }
    return false;
}

void SerialPort::readyReadNow(){
    emit readyRead();
}
