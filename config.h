#ifndef CONFIG_H
#define CONFIG_H
#include <QtSerialPort/QSerialPort>

#define Protocol_SSH "SSH"
#define Protocol_Serial "Serial"

typedef struct{

QString portName;

qint32 baudRate;

QSerialPort::DataBits dataBit;

QSerialPort::Parity parity;

QSerialPort::StopBits stopBits;

QSerialPort::FlowControl flowControl;

}SerialSetting;



typedef struct{
    QString name;
    QString protocol;

    QString portName;
    QString baudRate;
    QString dataBit;
    QString parity;
    QString stopBits;
    QString flowControl;
} Setting;

static bool transferToSerial(Setting *src,SerialSetting *dest);
static bool transferFromSerial(SerialSetting *src,Setting *dest);
#endif // CONFIG_H
