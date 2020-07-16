#include "configdialog.h"
#include "ui_configdialog.h"
#include "serialport.h"
#include <QDebug>

ConfigDialog::ConfigDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigDialog)
{
    ui->setupUi(this);
    QStringList list;
    list << Protocol_SSH << Protocol_Serial;
    ui->protocolBox->addItems(list);

    connect(ui->protocolBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(currentIndexChanged(QString)));

}

ConfigDialog::~ConfigDialog()
{
    if(mSerialForm != NULL){
        delete mSerialForm;
    }
    delete ui;
}

void ConfigDialog::currentIndexChanged(QString name){
    if(name == Protocol_SSH){

    }else if(name == Protocol_Serial){
        mSerialForm = new SerialForm(this);
        ui->centorLayout->addWidget(mSerialForm);
    }
}

void ConfigDialog::accept()
{
    QString protocol = ui->protocolBox->currentText();

    if(protocol == Protocol_SSH){

    }else if(protocol == Protocol_Serial){
        if(mSerialForm != NULL){
            SerialSetting *setting = new SerialSetting;
            if(mSerialForm->loadSerialSetting(setting)){
                SerialPort *port = new SerialPort(setting);
                emit postPort(qobject_cast<BasePort*>(port));
            }
        }
    }
    QDialog::accept();
}
