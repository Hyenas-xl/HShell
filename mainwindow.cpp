#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QDebug>
#include <QTextBlock>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createToolBar();
    connect(ui->actionConnect, SIGNAL(triggered(bool)), this, SLOT(serialOPerate()));
    connect(ui->actionDisConnect, SIGNAL(triggered(bool)), this, SLOT(serialOPerate()));
}

MainWindow::~MainWindow()
{
    if(connectDialog != NULL){
        delete connectDialog;
    }
    if(mPort != NULL){
        if(mPort->isOpen()){
            mPort->close();
        }
        delete mPort;
    }
    delete ui;
}

void MainWindow::createToolBar(){
    QAction *connectAction = new QAction(ui->mainToolBar);
    connectAction->setToolTip("Connect");
    connectAction->setObjectName("actionConnect");
    connectAction->setIcon(QIcon(":images/images/connect.png"));
    ui->mainToolBar->addAction(connectAction);

    QAction *quickAction = new QAction(ui->mainToolBar);
    quickAction->setToolTip("Quick Connect");
    quickAction->setObjectName("actionQuickConnect");
    quickAction->setIcon(QIcon(":images/images/quick_connect.png"));
    ui->mainToolBar->addAction(quickAction);

    QAction *disconnectAction = new QAction(ui->mainToolBar);
    disconnectAction->setToolTip("Disconnect");
    disconnectAction->setObjectName("actionDisConnect");
    disconnectAction->setIcon(QIcon(":images/images/disconnect.png"));
    ui->mainToolBar->addAction(disconnectAction);

    connect(connectAction,SIGNAL(triggered(bool)),this,SLOT(serialOPerate()));
    connect(quickAction,SIGNAL(triggered(bool)),this,SLOT(serialOPerate()));
    connect(disconnectAction,SIGNAL(triggered(bool)),this,SLOT(serialOPerate()));
}


void MainWindow::serialOPerate(){
    QAction *button = qobject_cast<QAction*>(sender());
    qDebug() << button->objectName();

    if(button->objectName() == "actionConnect"){
        if(connectDialog == NULL){
            connectDialog = new ConnectDialog;

            connect(connectDialog,SIGNAL(triggerPort(BasePort*)),this,SLOT(triggerPort(BasePort*)));
        }
        connectDialog->setModal(true);
        connectDialog->exec();
    }else if(button->objectName() == "actionDisConnect"){
        if(mPort != NULL){
            if(mPort->isOpen()){
                mPort->close();
            }
            delete mPort;
            mPort = NULL;
        }
    }else if(button->objectName() == "actionQuickConnect"){
        ConfigDialog *dialog = new ConfigDialog;
        connect(dialog,SIGNAL(postPort(BasePort*)),this,SLOT(triggerPort(BasePort*)));
        dialog->exec();
    }
}

void MainWindow::serialData(){
    QByteArray buf;

    buf=mPort->readAll();

    if(!buf.isEmpty()){
//        qDebug() << QString(buf);
        if(mIsCommand && mLength > 0){
            if(buf.length() >= mLength){
                QByteArray data = buf.mid(mLength);
//                qDebug() << "read: " << QString(data);
                ui->console->putData(data);
                data.clear();
                mIsCommand = false;
                mLength = -1;
            }else{
                mLength -= buf.length();
            }
            return ;
        }
//        qDebug() << "read: " << QString(buf);
        ui->console->putData(buf);
    }
    buf.clear();
}

void MainWindow::writeData(const QByteArray &data){
    if(mPort != NULL && mPort->isOpen()){
        qDebug() << "write : " << QString(data);
        mPort->write(data);
        mIsCommand = true;
        mLength = data.length();
    }
}

void MainWindow::triggerPort(BasePort *port){
    mPort = port;
    connect(ui->console, &Console::getData, this, &MainWindow::writeData);
    connect(mPort,SIGNAL(readyRead()),this,SLOT(serialData()));
    if(mPort->open(QIODevice::ReadWrite)){
        ui->console->setEnabled(true);
        ui->console->setLocalEchoEnabled(true);
    }else{
         QMessageBox::critical(this, "Open", "Open port failed.");
    }
}
