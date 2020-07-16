#include "config.h"


static bool transferToSerial(Setting *src, SerialSetting *dest){
    if(src->protocol == Protocol_Serial){
        dest->portName = src->portName;

        bool ok;
        QString baudRate = src->baudRate;
        int _baudRate = baudRate.toInt(&ok);
        if(!ok){
            return false;
        }
        dest->baudRate = _baudRate;


        QString dataBit = src->dataBit;
        if(dataBit == "5"){
            dest->dataBit = QSerialPort::Data5;
        }else if(dataBit == "6"){
            dest->dataBit = QSerialPort::Data6;
        }else if(dataBit == "7"){
            dest->dataBit = QSerialPort::Data7;
        }else if(dataBit == "8"){
            dest->dataBit = QSerialPort::Data8;
        }

        QString parity = src->parity;
        if(parity == "None"){
            dest->parity = QSerialPort::NoParity;
        }else if(parity == "Odd"){
            dest->parity = QSerialPort::OddParity;
        }else if(parity == "Even"){
            dest->parity = QSerialPort::EvenParity;
        }else if(parity == "Space"){
            dest->parity = QSerialPort::SpaceParity;
        }else if(parity == "Mark"){
            dest->parity = QSerialPort::MarkParity;
        }

        QString stopBit = src->stopBits;
        if(stopBit == "1"){
            dest->stopBits = QSerialPort::OneStop;
        }else if(stopBit == "1.5"){
            dest->stopBits = QSerialPort::OneAndHalfStop;
        }else if(stopBit == "2"){
            dest->stopBits = QSerialPort::TwoStop;
        }

        QString flowControl = src->flowControl;
        if(flowControl == "2"){
            dest->flowControl = QSerialPort::HardwareControl;
        }else if(flowControl == "3"){
            dest->flowControl = QSerialPort::SoftwareControl;
        }else{
            dest->flowControl = QSerialPort::NoFlowControl;
        }
        return true;
    }
    return false;
}


static bool transferFromSerial(SerialSetting *src, Setting *dest){
    dest->protocol = Protocol_Serial;
    dest->portName = src->portName;
    dest->baudRate = QString::number(src->baudRate);
    dest->dataBit = QString::number(src->dataBit);
    switch (src->parity) {
    case QSerialPort::NoParity:
        dest->parity = "None";
        break;
    case QSerialPort::OddParity:
        dest->parity = "Odd";
        break;
    case QSerialPort::EvenParity:
        dest->parity = "Even";
        break;
    case QSerialPort::SpaceParity:
        dest->parity = "Space";
        break;
    case QSerialPort::MarkParity:
        dest->parity = "Mark";
        break;
    }

    switch (src->flowControl) {
    case QSerialPort::HardwareControl:
        dest->stopBits = "2";
        break;
    case QSerialPort::SoftwareControl:
        dest->stopBits = "3";
        break;
    case QSerialPort::NoFlowControl:
        dest->stopBits = "1";
        break;
    }

    switch (src->stopBits) {
    case QSerialPort::OneStop:
        dest->stopBits = "1";
        break;
    case QSerialPort::OneAndHalfStop:
        dest->stopBits = "1.5";
        break;
    case QSerialPort::TwoStop:
        dest->stopBits = "2";
        break;
    }
    return true;
}
