#include "serialform.h"
#include "ui_serialform.h"
#include <QMessageBox>
#include <QDebug>

SerialForm::SerialForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialForm)
{
    ui->setupUi(this);
    QStringList ports;
    for(int i=1;i < 50;i++){
        ports << QString("COM%1").arg(i);
    }
    ui->portComboBox->addItems(ports);

    QStringList baudRates;
    baudRates << "1200" << "2400" << "4800" << "9600" << "19200" << "38400" << "57600" <<"115200";
    ui->baudRateComboBox->addItems(baudRates);

    QStringList dataBits;
    dataBits << "5" << "6" << "7" << "8";
    ui->dataBitsComboBox->addItems(dataBits);


    QStringList paritys;
    paritys << "None" << "Odd" << "Even" << "Space" << "Mark";
    ui->parityComboBox->addItems(paritys);

    QStringList stopBits;
    stopBits << "1" << "1.5" << "2";
    ui->stopBitsComboBox->addItems(stopBits);

    mButtonGroup = new QButtonGroup(this);
    mButtonGroup->addButton(ui->flowNoCheckBox,1);
    mButtonGroup->addButton(ui->flowHardwareCheckBox,2);
    mButtonGroup->addButton(ui->flowSoftwareCheckBox,3);
}

SerialForm::~SerialForm()
{
    delete mButtonGroup;
    delete ui;
}

bool SerialForm::loadSerialSetting(SerialSetting *setting){
    if(setting != NULL){
        setting->portName = ui->portComboBox->currentText();

        bool ok;
        QString baudRate = ui->baudRateComboBox->currentText();
        int _baudRate = baudRate.toInt(&ok);
        if(!ok){
            QMessageBox::critical(NULL, "BaudRate", "BaudRate need to be number.");
            return false;
        }
        setting->baudRate = _baudRate;


        QString dataBit = ui->dataBitsComboBox->currentText();
        if(dataBit == "5"){
            setting->dataBit = QSerialPort::Data5;
        }else if(dataBit == "6"){
            setting->dataBit = QSerialPort::Data6;
        }else if(dataBit == "7"){
            setting->dataBit = QSerialPort::Data7;
        }else if(dataBit == "8"){
            setting->dataBit = QSerialPort::Data8;
        }
        qDebug() << "dataBit: " << dataBit << " " << setting->dataBit;

        QString parity = ui->parityComboBox->currentText();
        if(parity == "None"){
            setting->parity = QSerialPort::NoParity;
        }else if(parity == "Odd"){
            setting->parity = QSerialPort::OddParity;
        }else if(parity == "Even"){
            setting->parity = QSerialPort::EvenParity;
        }else if(parity == "Space"){
            setting->parity = QSerialPort::SpaceParity;
        }else if(parity == "Mark"){
            setting->parity = QSerialPort::MarkParity;
        }

        QString stopBit = ui->stopBitsComboBox->currentText();
        if(stopBit == "1"){
            setting->stopBits = QSerialPort::OneStop;
        }else if(stopBit == "1.5"){
            setting->stopBits = QSerialPort::OneAndHalfStop;
        }else if(stopBit == "2"){
            setting->stopBits = QSerialPort::TwoStop;
        }

        qDebug() << "stopBit: " << stopBit << " " << setting->stopBits;

        int id = mButtonGroup->checkedId();
        switch (id) {
        case 2:
            setting->flowControl = QSerialPort::HardwareControl;
            break;
        case 3:
            setting->flowControl = QSerialPort::SoftwareControl;
            break;
        default:
            setting->flowControl = QSerialPort::NoFlowControl;
            break;
        }
        return true;
    }
    return false;
}

